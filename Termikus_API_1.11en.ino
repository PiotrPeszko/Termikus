/*
  Copyright ©2020 Piotr Peszko
  www.peszko.net
  piotr@peszko.net

  This is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This software is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  -----------------------------------------------------------------------------------------------
  Termikus version 1.11e 2020-02-28 english UI and most of the comments
  Termikus version 1.11 2020-02-14 UI beautyfied
  Termikus version 1.10 2020-01-02 REST API
  Termikus version 1.01 2020-01-02 First public version
  -----------------------------------------------------------------------------------------------
  Acknowledgments:
  
  TERMIKUS became what it is thanks to the work of the following people:
  
  WLAN Management based on ESP_WebConfig by John LassenESP_WebConfig
  Copyright (c) 2015 John Lassen. All rights reserved.

  ArduinoJson library Copyright © 2014-2019 Benoit BLANCHON and used according to The MIT License (MIT)
  Copyright © 2014-2019 Benoit BLANCHON

  Thingspeak library copyright: 2017, The MathWorks, Inc.

  DallasTemperature "version": "3.8.0", copyrights Milles Burton

  OneWire  "version": "2.3.5", copyrights Paul Stoffregen 

  ArduinoJson "version": "5.11.2", copyrights Benoit Blanchon
  
*/

/*
   Utility Libraries
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>
#include <OneWire.h>              // "version": "2.3.5"
#include <DallasTemperature.h>    // "version": "3.8.0"
#include <ThingSpeak.h>           
#include <FS.h>					//if you do not want to have real favicon you can comment this line and change favicon routing, lines 163-167 
#include <ArduinoJson.h>          //"version": "5.11.2"
#include <EEPROM.h>
#include <WiFiUdp.h>

#include "helpers.h"
#include "global.h"
#include "thermostat.h"
#include "json.h"
#include "Page_Admin.h"
#include "Page_SafeMode.h"
#include "Page_Script.js.h"
#include "Page_Style.css.h"
#include "Page_NTPsettings.h"
#include "Page_Information.h"
#include "Page_Intervals.h"
#include "Page_General.h"
#include "PAGE_NetworkConfiguration.h"
#include "PAGE_Termikus.h"
#include "Page_Program1.h"
#include "Page_Program2.h"
#include "Page_Program3.h"
#include "Page_Program4.h"
#include "Page_Program5.h"
#include "Page_Program6.h"
#include "Page_Program7.h"
#include "Page_Program8.h"


#define ACCESS_POINT_NAME  "TERMOSTAT"
#define ACCESS_POINT_PASSWORD  "12345678"
#define AdminTimeOut 500                   // Defines the Time in Seconds, when the Admin-Mode will be disabled

//*********************************
// OneWire definitions
//*********************************
#define ONEWIRE_PIN 14        //OneWire pin 
OneWire oneWire(ONEWIRE_PIN); //OneWire bus declaration

//**********************************
// DS18B20 sensor definitions
//**********************************
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
byte deviceCount = 0;               //used to check if the sensor is there

//*********************************
//     Thingspeak variables
//*********************************
static char buffer[15];
bool thingsUpdated = 0;           //used to assure one update in a minute
char* myWriteAPIKey = "0";
char* host = "api.thingspeak.com";

//*********************************
//     WiFi definitions
//*********************************

const int httpPort = 80;
WiFiClient client;

//*********************************
//     Other utilities
//*********************************

unsigned long startMills;


// ***** SETUP *****
void setup ( void ) {
  EEPROM.begin(4096);
  Serial.begin(115200);
  SPIFFS.begin();                 // Start the SPI Flash Files System
  pinMode(RELAY_PIN, OUTPUT);     //relay initiation
  relayOff();
  pinMode(LED_PIN, OUTPUT);       //LED initiation
  ledOff();
  pinMode(BUTTON_PIN, INPUT);     //button initiation

  startMills = millis();

  Serial.println("Reading configuration data...");
  if (!ReadConfig())
  {
    firstStartGeneralConfig ();      // assign general config values at first start
    WriteConfig();                   // write general config to EEPROM
    firstStartProgramConfig ();      // load default program data and write them to EEPROM
    Serial.println("General config applied");
  } else {                          // retrieve program data from memory since config is already there
    for (byte x = 1; x < 17; x++) {
      readProgram(x);
    }
    Serial.println("Program data retrieved from memory");
  }

  resDS = resDsTranslate();         //function translating DS resolution from number to text representation held in resDS. resDS must be ready for API

  if (AdminEnabled)                 // WiFi start in Soft AP at reset or first start
  {
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(ACCESS_POINT_NAME , ACCESS_POINT_PASSWORD);
  } else {
    WiFi.mode(WIFI_STA);
  }

  ConfigureWifi();                  // SSID and pasword configuration. If no DHCP, ip, gateway and netmask configuration

  /*****
     Server routing functions
  *****/
  server.on ( "/", []() {
    Serial.println("admin.html");
    server.send ( 200, "text/html", PAGE_AdminMainPage );
  }  );
  
  //if you do not want to use file system, comment the following line
  server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico"); 
  
  //if you do not want to use file system, uncomment this line:
  //server.on ( "/favicon.ico",   []() { Serial.println("favicon.ico"); server.send ( 200, "text/html", "" );   }  );
  

  server.on ( "/style.css", []() {
    Serial.println("style.css");
    server.send ( 200, "text/plain", PAGE_Style_css );
  } );
  server.on ( "/microajax.js", []() {
    Serial.println("microajax.js");
    server.send ( 200, "application/javascript", PAGE_microajax_js );
  } );
  server.on ( "/admin.html", []() {
    Serial.println("admin.html");
    server.send ( 200, "text/html", PAGE_AdminMainPage );
  }  );
  server.on ( "/info.html", []() {
    Serial.println("info.html");
    server.send ( 200, "text/html", PAGE_Information );
  }  );
  server.on ( "/termikus.html", []() {
    server.send ( 200, "text/html", PAGE_Termikus );
  } );

  server.on ( "/config.html", send_network_configuration_html );
  server.on ( "/ntp.html", send_NTP_configuration_html  );
  server.on ( "/general.html", send_general_html  );
  server.on ( "/safemode.html", send_safemode_html  );
  server.on ( "/intervals.html", send_intervals_values );
  server.on ( "/program1.html", save_program1_values );
  server.on ( "/program2.html", save_program2_values );
  server.on ( "/program3.html", save_program3_values );
  server.on ( "/program4.html", save_program4_values );
  server.on ( "/program5.html", save_program5_values );
  server.on ( "/program6.html", save_program6_values );
  server.on ( "/program7.html", save_program7_values );
  server.on ( "/program8.html", save_program8_values );

  // window.onload routing

  server.on ( "/admin/values", send_network_configuration_values_html );
  server.on ( "/admin/connectionstate", send_connection_state_values_html );
  server.on ( "/admin/infovalues", send_information_values_html );
  server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
  server.on ( "/admin/generalvalues", send_general_configuration_values_html);
  server.on ( "/admin/safemodevalues", send_safemode_values_html);
  server.on ( "/admin/filldynamicdata", filldynamicdata );
  server.on ( "/admin/program_values1", send_programator_values1_html);
  server.on ( "/admin/program_values2", send_programator_values2_html);
  server.on ( "/admin/program_values3", send_programator_values3_html);
  server.on ( "/admin/program_values4", send_programator_values4_html);
  server.on ( "/admin/program_values5", send_programator_values5_html);
  server.on ( "/admin/program_values6", send_programator_values6_html);
  server.on ( "/admin/program_values7", send_programator_values7_html);
  server.on ( "/admin/program_values8", send_programator_values8_html);
  server.on ( "/admin/intervals", send_intervals_values_html);

  //API routing

  server.on("/get_info", HTTP_GET, get_status);
  server.on("/get_temp", HTTP_GET, get_temperatures);
  server.on("/get_interval", HTTP_GET, get_interval);
  server.on("/get_prog", HTTP_POST, post_put);
  server.on("/write", HTTP_PUT, post_put);

  server.onNotFound ( []() {
    //Serial.println("Page not found");
    server.send ( 400, "text/html", "<p style=\"font-size:1em;\">Page not found</p>" );
  }  );

  server.begin();

  Serial.println( "HTTP server started" );

  tkSecond.attach(1, Second_Tick);    // ticker attached for 1 sec tasks

  UDPNTPClient.begin(2390);      // Port for NTP receive

  sensors.begin();                    // sensor object initiation

  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount(); // Search for devices on the bus and assign based on an index.
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sonsor(s).");
  if (!sensors.getAddress(insideThermometer, 0)) {
    Serial.println("No sensor found.");
    ledOn();
  }
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();
  sensors.setResolution(insideThermometer, config.ds_resolution); // set the resolution to the value stored in config.ds_resolution
  Serial.print("Device 0 Resolution: ");
  config.ds_resolution = sensors.getResolution(insideThermometer);
  Serial.println(config.ds_resolution);

  ThingSpeak.begin(client);             // Start thingspeak client
  thingspeakTranslate();                // convert server name and paswd to char array
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}


//***LOOP*****LOOP*****LOOP*****LOOP*****LOOP************************
void loop ( void ) {

  /*
  * ***** Button handling *************
  */
  reading = digitalRead(BUTTON_PIN);    // read the button input

  if (reading != lastReading) {
    lastDebounceTime = millis();      // reset the debouncing timer
    // if there was no change lastDebounceTime remais the old value
  }

  if ((millis() - lastDebounceTime) > debounceDelay) // does debounce time elapsed?
  {
    if (reading != lastButtonState) {
      if (lastButtonState == HIGH && reading == LOW) // the button was pressed
      {
        startPressed = millis();

      } else if (lastButtonState == LOW && reading == HIGH) { // the button was released
        endPressed = millis();
        timeHold = endPressed - startPressed;
        if (timeHold >= 5000) {                     // Action: User induces AP mode
          WiFi.mode(WIFI_AP_STA);
          WiFi.softAP(ACCESS_POINT_NAME , ACCESS_POINT_PASSWORD);
          ledOn();
          delay(1000);
          ledOff();
          AdminEnabled = true;
          AdminTimeOutCounter = 0;
        }

        if (timeHold >= 300 && timeHold < 5000) {  // Physical confirmation of a configuration changes in safe mode
          Serial.println("Button >1 sec < 5sec: Program data saved to hot bank.");
          if (!config.enableSafety && config.enableSafetyTemp) {  //safety turned off
            config.enableSafetyTemp = false;
            EEPROM.write(10, config.enableSafetyTemp);
            EEPROM.commit();
            reWrite();            // program data rewritten from cold to hot memory
            ledOff();             //setting LED off
          } else if (config.enableSafety && config.enableSafetyTemp) {  //safe mode enabled, only program data are rewritten to hot memory
            reWrite();            // program data rewritten from cold to hot memory
            ledOff();             //setting LED off
          }
        }

      } // end of button release IF
    }
    lastButtonState = reading;
  }
  lastReading = reading;

  if (AdminEnabled)           // Soft AP mode disabled on AdminTimeOut elapsed
  {
    if (AdminTimeOutCounter > AdminTimeOut)
    {
      AdminEnabled = false;
      Serial.println("Admin Mode off!");
      WiFi.mode(WIFI_STA);
      delay(1000);
    }
  }

  if (config.Update_Time_Via_NTP_Every  > 0 )  // NTP time update
  {
    if (cNTP_Update > 10 && firstStart)  // If first NTP update failed, it will be repeated every 10 sec, untill firstStart=false (which happens only after first successful NTP update)
    {
      NTPRefresh();
      cNTP_Update = 0;      // conuter for NTP refresh zeroed, will be incremented at secondTik
    }
    else if ( cNTP_Update > (config.Update_Time_Via_NTP_Every * 60) )
    {
      NTPRefresh();
      cNTP_Update = 0;
    }
  }

  /*****
    The main function - keeping the temperature on the set level "setTemp"
    setTemp is assigned with a value coming from checkProgTemp function.
    checkProgTemp funtion checks which program temperature, or main temperature or interval temeprature shall be applied
  *****/

  if (ds_resolution == 1) {                              // updates DS resolution if necessary
    setDSResolution();
    ds_resolution = 0;
  }
  if (millis() - startMills >= 1000 && deviceCount > 0) //temperature check every second if there is DS18B20 detected
  {
    startMills = millis();
    sensors.requestTemperatures();                      // Send the command to get temperatures from sensors
    setTemp = checkProgTemp();                          // returns the program temperature or base temperature or the interval temperature if enabled
    measureTemp = sensors.getTempC(insideThermometer);  // requests the temmperature from sensor

    /*
       RELAY management - heating mode
    */
    if (measureTemp < (setTemp - config.histeresisLower) && relayStatus == false && config.coolMode == false)
    {
      relayStatus = true;
      Serial.println ("Heating ON");
      relayOn();
      //printTemperatures(setTemp, measureTemp);
    }
    if (measureTemp > (setTemp + config.histeresisUpper) && relayStatus == true && config.coolMode == false)
    {
      relayStatus = false;
      Serial.print ("Heating OFF");
      relayOff();
      //printTemperatures(setTemp, measureTemp);
    }

    /*
       RELAY management - cooling mode
    */
    if (measureTemp < (setTemp - config.histeresisLower) && relayStatus == true && config.coolMode == true)
    {
      relayStatus = false;
      Serial.println ("Cooling OFF");
      relayOff();
      //printTemperatures(setTemp, measureTemp);
    }
    if (measureTemp > (setTemp + config.histeresisUpper) && relayStatus == false && config.coolMode == true)
    {
      relayStatus = true;
      Serial.println ("Colling ON");
      relayOn();
      //printTemperatures(setTemp, measureTemp);
    }
  }

  /******
    Thingspeek update
  *****/
  if (updateTH == 1) {
    thingspeakTranslate();
    updateTH = 0;
  }

  if (config.enableThingspeak == true && WiFi.status() == WL_CONNECTED) {
    if (DateTime.minute % config.hostUpdatePeriod == 0 && thingsUpdated == false)
    {
      yield();
      delay(100 * config.DeviceNumber);
      int heap = ESP.getFreeHeap();
      ThingSpeak.setField(1, measureTemp);
      ThingSpeak.setField(2, setTemp);
      ThingSpeak.setField(3, relayStatus);
      ThingSpeak.setField(4, heap);       //optional free heap data collection
      channelUpdateStatus = ThingSpeak.writeFields(config.hostChannelNumber, myWriteAPIKey);
      thingsUpdated = true;
    }
    if (DateTime.minute % config.hostUpdatePeriod != 0 && thingsUpdated == true) {
      thingsUpdated = false;
    }
  }
  // *** END Thingspeek update ***

  /******
     Interval on/off function. If interval is ON, the thermostat function will take the interval temperature to be kept.
  *****/
  if (intervalDuration > 0 && intervalMode == false) {
    intervalMode = true;
    intervalSecCountdown = intervalDuration * 60;
    intervalCountdownTk.attach(1, intervalCountdown);
  } else if (intervalDuration == 0 && intervalMode == true) {
    intervalMode = false;
    intervalSecCountdown = 0;
    intervalCountdownTk.detach();
  }

  server.handleClient();


}
//***************Loop ends here***************
//*********************************************

/*****
  The  function translates thingspeak server name and write key from string to char array to be usable by the thingspeak library
*****/
void thingspeakTranslate (void) { // config data translated to varialbles accepted by thingspeak.h
  config.hostServerName.toCharArray(host, config.hostServerName.length() + 1);
  config.hostWriteKey.toCharArray(myWriteAPIKey, config.hostWriteKey.length() + 1);
}

/*****
  DS18B20 address printout function
*****/
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
/*****
  The function sets the DS18B20 resolution. Used @ startup & user configuration change @page_general
*****/
void setDSResolution() {
  sensors.setResolution(insideThermometer, config.ds_resolution); // ustawia rozdzielczość
}
