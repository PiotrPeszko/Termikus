#ifndef GLOBAL_H
#define GLOBAL_H

ESP8266WebServer server(80);					// The Webserver
boolean firstStart = true;						// On firstStart = true, NTP will try to get a valid time, if successful then firstStart=false
int AdminTimeOutCounter = 0;					// Counter for Disabling the AdminMode
WiFiUDP UDPNTPClient;                 // NTP Client
strDateTime DateTime;									// Global DateTime structure, will be refreshed every Second
unsigned long UnixTimestamp = 0;			// GLOBALTIME  ( Will be set by NTP)
int cNTP_Update = 0;									// Counter for Updating the time via NTP
Ticker tkSecond;											// Second - Timer for Updating Datetime Structure
boolean ntpFail = false;              // NTP time update fail indication
boolean AdminEnabled = true;		      // Enable Admin Mode for a given Time
byte programFit;                      // The number of the program that fits the current time
byte ds_resolution = 0;               // Helper variable to set DS resolution
String resDS;                         // Helper string to hold DS resolution in readable format
boolean updateTH = 0;                 // Helper variable to notify the convertion for char array is necessary
int channelUpdateStatus = 0;          // Helper variable with the last thingspeak update status

//**************************************
//    Interval temperature steering
//**************************************

boolean intervalMode = false;
float intervalTemperature = 18;
unsigned int intervalDuration = 0;
Ticker intervalCountdownTk;             // Coundown for interval steering
unsigned int intervalSecCountdown;

//**************************************
// PIN Definitions, button, onboard LED
//**************************************

#define RELAY_PIN 12    // relay GPIO12 (as in sonoff TH10)
#define BUTTON_PIN 0    // button GPIO in SONOFF
#define LED_PIN 13      // status LED in SONOFF

bool relayStatus = false; // relay status (on/off)

//***************************
// Button handling variables
//***************************

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time

boolean reading = 1;
boolean lastReading = 1;
boolean lastButtonState = 1; // previous state of the button

unsigned long startPressed = 0;    // the time button was pressed
unsigned long endPressed = 0;      // the time button was released
unsigned long timeHold = 0;        // the time button was hold

/*****
Structure holding general configuration data
*****/
struct strConfig {
	String ssid;
	String password;
	byte  IP[4];
	byte  Netmask[4];
	byte  Gateway[4];
	boolean dhcp;
	String ntpServerName;
	unsigned long Update_Time_Via_NTP_Every;
	long timezone;
	boolean daylight;
	String DeviceName;
  byte DeviceNumber;
  float baseTemp;
  float histeresisLower;
  float histeresisUpper;
  byte ds_resolution;
  String hostServerName;
  byte hostUpdatePeriod;
  unsigned long hostChannelNumber;
  String hostWriteKey;
  boolean enableThingspeak;
  boolean enableAPI;
  boolean enableSafety;
  boolean enableSafetyTemp;
  boolean coolMode;
}   config;

void ledOn(){
  digitalWrite(LED_PIN, LOW);    //setting LED On
}
void ledOff(){
  digitalWrite(LED_PIN, HIGH);    //setting LED off
}
void relayOn(){
  digitalWrite(RELAY_PIN, HIGH);    //setting RELAY On
}
void relayOff(){
  digitalWrite(RELAY_PIN, LOW);    //setting RELAY Off
}

/*****
WiFi Configuration
*****/
void ConfigureWifi()
{
	Serial.println("Configuring Wifi");
	WiFi.begin (config.ssid.c_str(), config.password.c_str());
	if (!config.dhcp)
	{
		WiFi.config(IPAddress(config.IP[0],config.IP[1],config.IP[2],config.IP[3] ),  IPAddress(config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3] ) , IPAddress(config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3] ));
	}
}

/*****
General configuration writing to EEPROM
*****/

void WriteConfig()
{
  int next;
	Serial.println("Writing Config");

  if (config.enableSafety==false && config.enableSafetyTemp==true){
    ledOn();
  }
 
	EEPROM.write(0,'C');
	EEPROM.write(1,'F');
	EEPROM.write(2,'G');

EEPROM.write(10,config.enableSafetyTemp);

	EEPROM.write(16,config.dhcp);
	EEPROM.write(17,config.daylight);
  next = EEPROMAnythingWrite(18, reinterpret_cast<char*>(&config.Update_Time_Via_NTP_Every), sizeof(config.Update_Time_Via_NTP_Every)); // 4 Byte
  next = EEPROMAnythingWrite(22, reinterpret_cast<char*>(&config.timezone), sizeof(config.timezone)); // 4 Byte
  EEPROM.write(27,config.DeviceNumber);  //the number used to calculate time offset for Thingspeak raports in case multiple devices are used in one LAN
  EEPROM.write(28,config.coolMode);
  EEPROM.write(29,config.enableSafety);
  EEPROM.write(30,config.enableAPI);
  EEPROM.write(31,config.enableThingspeak);
  
	EEPROM.write(32,config.IP[0]);
	EEPROM.write(33,config.IP[1]);
	EEPROM.write(34,config.IP[2]);
	EEPROM.write(35,config.IP[3]);

	EEPROM.write(36,config.Netmask[0]);
	EEPROM.write(37,config.Netmask[1]);
	EEPROM.write(38,config.Netmask[2]);
	EEPROM.write(39,config.Netmask[3]);

	EEPROM.write(40,config.Gateway[0]);
	EEPROM.write(41,config.Gateway[1]);
	EEPROM.write(42,config.Gateway[2]);
	EEPROM.write(43,config.Gateway[3]);

  EEPROM.write(44,config.hostUpdatePeriod);
  
  next = EEPROMAnythingWrite(45, reinterpret_cast<char*>(&config.hostChannelNumber), sizeof(config.hostChannelNumber)); // 4 Byte
  next = EEPROMAnythingWrite(49, reinterpret_cast<char*>(&config.ds_resolution), sizeof(config.ds_resolution));         // 1 Byte
  EEPROMWritelong(50, config.baseTemp);
  next = EEPROMAnythingWrite(54, reinterpret_cast<char*>(&config.histeresisUpper), sizeof(config.histeresisUpper));     // 4 Byte  
  next = EEPROMAnythingWrite(58, reinterpret_cast<char*>(&config.histeresisLower), sizeof(config.histeresisLower));     // 4 Byte  
    
	WriteStringToEEPROM(64,config.ssid);            // 32 Byte
	WriteStringToEEPROM(96,config.password);        // 32 Byte
	WriteStringToEEPROM(128,config.ntpServerName);  // 32 Byte
	WriteStringToEEPROM(160,config.DeviceName);     // 32 byte
  WriteStringToEEPROM(192,config.hostServerName); //32 byte
  WriteStringToEEPROM(224,config.hostWriteKey);   //32 byte
  
  EEPROM.commit();
}

/*****
Reading configuration from EEPROM
*****/

boolean ReadConfig()
{
	Serial.println("Reading Configuration");
	if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' )
	{
    int next;
    Serial.println("Configurarion Found!");
		
		config.enableSafetyTemp=EEPROM.read(10);    
    
		config.dhcp = 	EEPROM.read(16);
		config.daylight = EEPROM.read(17);
		config.Update_Time_Via_NTP_Every = EEPROMReadlong(18); // 4 Byte
    //next = EEPROMAnythingRead(18, reinterpret_cast<char*>(&config.Update_Time_Via_NTP_Every), sizeof(config.Update_Time_Via_NTP_Every));
		next = EEPROMAnythingRead(22, reinterpret_cast<char*>(&config.timezone), sizeof(config.timezone));
		//config.timezone = EEPROMReadlong(22); // 4 Byte
    
    config.DeviceNumber = EEPROM.read(27);
    config.coolMode=EEPROM.read(28);
    config.enableSafety=EEPROM.read(29);    
    config.enableAPI=EEPROM.read(30);
    config.enableThingspeak=EEPROM.read(31);
		config.IP[0] = EEPROM.read(32);
		config.IP[1] = EEPROM.read(33);
		config.IP[2] = EEPROM.read(34);
		config.IP[3] = EEPROM.read(35);
		config.Netmask[0] = EEPROM.read(36);
		config.Netmask[1] = EEPROM.read(37);
		config.Netmask[2] = EEPROM.read(38);
		config.Netmask[3] = EEPROM.read(39);
		config.Gateway[0] = EEPROM.read(40);
		config.Gateway[1] = EEPROM.read(41);
		config.Gateway[2] = EEPROM.read(42);
		config.Gateway[3] = EEPROM.read(43);
    config.hostUpdatePeriod = EEPROM.read(44);
    //config.hostChannelNumber = EEPROMReadlong(45); // 4 Byte
    next = EEPROMAnythingRead(45, reinterpret_cast<char*>(&config.hostChannelNumber), sizeof(config.hostChannelNumber));
    next = EEPROMAnythingRead(49, reinterpret_cast<char*>(&config.ds_resolution), sizeof(config.ds_resolution));
        
    config.baseTemp = EEPROMReadlong(50);
    
    next = EEPROMAnythingRead(54, reinterpret_cast<char*>(&config.histeresisUpper), sizeof(config.histeresisUpper));
    next = EEPROMAnythingRead(58, reinterpret_cast<char*>(&config.histeresisLower), sizeof(config.histeresisLower));
   
		config.ssid = ReadStringFromEEPROM(64);
		config.password = ReadStringFromEEPROM(96);
		config.ntpServerName = ReadStringFromEEPROM(128);

		config.DeviceName= ReadStringFromEEPROM(160);
    config.hostServerName = ReadStringFromEEPROM(192);
    config.hostWriteKey = ReadStringFromEEPROM(224);
       
		return true;
		Serial.print ("Safety: ");
    Serial.print (config.enableSafety);
    Serial.println (config.enableSafetyTemp);
	}
	else
	{
		Serial.println("Configurarion NOT FOUND!!!!");
		return false;
	}
}

/*****
Determining memory bank for program data to save in/read from
*****/
byte progNumber;                      // hepler variabe passing info to the function below on program number
byte memoryBank;                      // helper variable to assigne the right address while saving configuration data, used on Page_Program sites

byte whichMemoryBank (byte progNumber){
  if (!config.enableSafety){
    memoryBank=progNumber;
  } else if (config.enableSafety){
    memoryBank=progNumber+8;
  }
  Serial.println (memoryBank);
}



/*****
NTP functions and time keeping
*****/

const int NTP_PACKET_SIZE = 48; 
byte packetBuffer[NTP_PACKET_SIZE]; 


unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  UDPNTPClient.beginPacket(address, 123); //NTP requests are to port 123
  UDPNTPClient.write(packetBuffer, NTP_PACKET_SIZE);
  UDPNTPClient.endPacket();
}

void NTPRefresh()
{
	if (WiFi.status() == WL_CONNECTED)
	{
		IPAddress timeServerIP; 
		WiFi.hostByName(config.ntpServerName.c_str(), timeServerIP); 
    sendNTPpacket(timeServerIP); // send an NTP packet to a time server
    Serial.println("Waiting for NTP packet");
    delay(1000);
    int cb = UDPNTPClient.parsePacket();
		if (!cb) {
			Serial.println("no NTP packet yet");
		} else {
			Serial.print("NTP packet received, length=");
			Serial.println(cb);
			UDPNTPClient.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
			unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
			unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      // combine the four bytes (two words) into a long integer
      // this is NTP time (seconds since Jan 1 1900):
			unsigned long secsSince1900 = highWord << 16 | lowWord;
			const unsigned long seventyYears = 2208988800UL;
			unsigned long epoch = secsSince1900 - seventyYears;
			UnixTimestamp = epoch;
      firstStart = false; 
		}
	}
}

void Second_Tick()
{
	AdminTimeOutCounter++;
	cNTP_Update++;
  UnixTimestamp++;
  	strDateTime tempDateTime;
  	ConvertUnixTimeStamp(UnixTimestamp +  (config.timezone *  360) , &tempDateTime);
  	if (config.daylight) // Summertime correction
  		if (summertime(tempDateTime.year,tempDateTime.month,tempDateTime.day,tempDateTime.hour,0))
  		{
  			ConvertUnixTimeStamp(UnixTimestamp +  (config.timezone *  360) + 3600, &DateTime);
  		}
  		else
  		{
  			DateTime = tempDateTime;
  		}
  	else
  	{
  			DateTime = tempDateTime;
  	}
}


void intervalCountdown (){
  intervalSecCountdown=intervalSecCountdown-1;
  if (intervalSecCountdown==0) {
    intervalMode = false;
    intervalDuration = 0;
    intervalCountdownTk.detach();
  }
}

/*****
Function converts ds_resolution from number to readable format for presentation on temperatures.html (page_termikus.h)
******/
String resDsTranslate(){   
  String resDS;
  switch (config.ds_resolution) {
    case 9:
      resDS = "0.5";
      return resDS;
    case 10:
      resDS = "0.25";
      return resDS;
    case 11:
      resDS = "0.125";
      return resDS;
    case 12:
      resDS = "0.0625";
      return resDS;
    }
}

/*****
The function converting seconds to minutes for Page_intervals.h and json.h
******/
unsigned int timeToGoConv (){   
  unsigned int timeToGo;
  if (intervalSecCountdown==0){
      timeToGo=0;
    } else if (intervalSecCountdown<60) {
      timeToGo=1;
    } else {
      timeToGo = intervalSecCountdown/60;
    }
    return timeToGo;
}

#endif
