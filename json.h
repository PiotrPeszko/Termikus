#ifndef JSON_H
#define JSON_H


/*
 The file contains REST API definition for Termikus
  Getting information from Termikus:

  CHECKING
  General configuration information (HTTP_GET): 
  curl -i http://192.168.1.104/get_info 
  
  Information on temperatures and relay status (HTTP_GET):
  curl -i http://192.168.1.104/get_temp 
  
  Interval steering information (HTTP_GET):
  curl -i http://192.168.1.104/get_interval  

  Program data information: 
  curl -i -X POST -d {\"PROGRAM\":\"read\",\"NUMBER\":\"1\"} http://192.168.1.104/get_prog

  MODIFICATIONS
  All object modification request are sent to the same address http://x.x.x.x/write with method HTTP_PU, but differs in paylod content.
  
  Interval steering start:
  curl -i -X PUT -d {\"INTERVAL\":\"true\",\"iTemp\":\"35\",\"iDuration\":\"15\"} http://192.168.1.104/write

  Storing new program data:
  curl -i -X PUT -d {\"PROGRAM\":\"1\",\"hSTART\":\"0\",\"mSTART\":\"0\",\"hSTOP\":\"6\",\"mSTOP\":\"0\",\"TEMP\":\"26.5\",\"PN\":\"1\",\"WT\":\"1\",\"SR\":\"1\",\"CZ\":\"1\",\"PT\":\"1\",\"SO\":\"1\",\"ND\":\"1\",\"ENABLE\":\"1\"} http://192.168.1.104/write

  PROGRAM = program number 1-8
  
  Storing new general temperature (program 9)
  curl -i -X PUT -d {\"PROGRAM\":\"9\",\"TEMP\":\"35\"} http://192.168.1.104/write
   
*/


void get_status() {
    StaticJsonBuffer<280> jsonBuffer;
    JsonObject& jsonObj = jsonBuffer.createObject();
    char JSONmessageBuffer[280];

    jsonObj["DeviceName"] = (String)config.DeviceName;
    jsonObj["DeviceNumber"] = (String)config.DeviceNumber;
    jsonObj["SafetyStatus"] = (String)config.enableSafety + (String)config.enableSafetyTemp;
    jsonObj["mainTemp"] = (String)config.baseTemp;
    jsonObj["measurTemp"] = (String)measureTemp;
    jsonObj["activeProg"] = (String)programFit;
    jsonObj["progTemp"] = (String) setTemp;
    jsonObj["relayStatus"] = relayStatus;
    jsonObj["upHist"] = (String) config.histeresisUpper;
    jsonObj["loHist"] = (String) config.histeresisLower;
    jsonObj["dsRes"] = (String) resDS;
    jsonObj["coolMode"] = config.coolMode;
    jsonObj["thspStatus"] = (String) channelUpdateStatus;
    jsonObj.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    server.send(200, "application/json", JSONmessageBuffer);
}

void get_temperatures() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& jsonObj = jsonBuffer.createObject();
    char JSONmessageBuffer[200];

    jsonObj["measurTemp"] = (String)measureTemp;
    jsonObj["mainTemp"] = (String)config.baseTemp;
    jsonObj["activeProg"] = (String)programFit;
    jsonObj["progTemp"] = (String) setTemp;
    jsonObj["relayStatus"] = relayStatus;
    
    jsonObj.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    server.send(200, "application/json", JSONmessageBuffer);
}


void get_interval() {
    StaticJsonBuffer<115> jsonBuffer;
    JsonObject& jsonObj = jsonBuffer.createObject();
    char JSONmessageBuffer[115];

    unsigned int timeToGo = timeToGoConv();  // interval elapsed time second to minutes convertion
    
    jsonObj["interval"] = intervalMode;
    jsonObj["iTemp"] = (String)intervalTemperature;
    jsonObj["iDuration"] = (String)intervalDuration;
    jsonObj["timeToGo"] = (String)timeToGo;
    jsonObj.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    server.send(200, "application/json", JSONmessageBuffer);
}

void post_program(byte number){
    StaticJsonBuffer<250> jsonBuffer;
    JsonObject& jsonObj = jsonBuffer.createObject();
    char JSONmessageBuffer[250];
      jsonObj["PROGRAM"] = number;
      jsonObj["hSTART"] = progData[number].startH;
      jsonObj["mSTART"] = progData[number].startM;
      jsonObj["hSTOP"] = progData[number].stopH;
      jsonObj["mSTOP"] = progData[number].stopM;
      jsonObj["TEMP"] = progData[number].tempProgramu;
      jsonObj["PN"] = progData[number].Pn;
      jsonObj["WT"] = progData[number].Wt;
      jsonObj["SR"] = progData[number].Sr;
      jsonObj["CZ"] = progData[number].Cz;
      jsonObj["PT"] = progData[number].Pt;
      jsonObj["SO"] = progData[number].So;
      jsonObj["ND"] = progData[number].Nd;
      jsonObj["ENABLE"] = progData[number].Enabled;
      
      jsonObj.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      server.send(200, "application/json", JSONmessageBuffer);
}


void json_to_interval(JsonObject& jsonBody) {
    float iTemp;
    unsigned int iDuration;

    iTemp = jsonBody["iTemp"];
    iDuration = jsonBody["iDuration"];
    
    if (iTemp > 125) iTemp = 125;
    if (iTemp < -55) iTemp = -55;
    if (iDuration < 0) iDuration = 0;
    if (iDuration > 65000) iDuration = 65000;
    
    Serial.println(iTemp);
    Serial.println(iDuration);

    intervalTemperature = iTemp;
    intervalDuration = iDuration;
}

void json_to_program (JsonObject& jsonBody, byte number) {
    byte hStart, mStart, hStop, mStop;
    float Temperature;
    boolean pn, wt, sr, cz, pt, so, nd, enabled;
    
    hStart = jsonBody["hSTART"];
    mStart = jsonBody["mSTART"];
    hStop = jsonBody["hSTOP"];
    mStop = jsonBody["mSTOP"];
    Temperature = jsonBody["TEMP"];
    pn = jsonBody["PN"]; // weekdays starting Monday
    wt = jsonBody["WT"];
    sr = jsonBody["SR"];
    cz = jsonBody["CZ"];
    pt = jsonBody["PT"];
    so = jsonBody["SO"];
    nd = jsonBody["ND"];
    enabled = jsonBody["ENABLE"];

    if (hStart > 23 || hStart < 0) hStart = 0;
    if (hStop > 23 || hStop < 0) hStop = 0;
    if (mStart > 59 || mStart < 0) mStart = 0;
    if (mStop > 59 || mStop < 0) mStop = 0;
    if (Temperature > 125) Temperature = 125;
    if (Temperature < -55) Temperature = -55;
    if (Temperature > -55 && Temperature < 125) progData[number].tempProgramu = Temperature;
    if (hStart >= 0 || hStart <= 23) progData[number].startH = hStart;
    if (mStart >= 0 || mStart <= 59) progData[number].startM = mStart;
    if (hStop >= 1 || hStop <= 23) progData[number].stopH = hStop;
    if (mStop >= 0 || mStop <= 59) progData[number].stopM = mStop;
    if (pn == false || pn == true) progData[number].Pn = pn;
    if (wt == false || wt == true) progData[number].Wt = wt;
    if (sr == false || sr == true) progData[number].Sr = sr;
    if (cz == false || cz == true) progData[number].Cz = cz;
    if (pt == false || pt == true) progData[number].Pt = pt;
    if (so == false || so == true) progData[number].So = so;
    if (nd == false || nd == true) progData[number].Nd = nd;
    if (enabled == true || enabled == false) progData[number].Enabled = enabled;
    writeProgram(number);
}

void json_to_temperature(JsonObject& jsonBody) {
  float Temperature;
  Temperature = jsonBody["TEMP"];

  if (Temperature > 125) Temperature = 125;
  if (Temperature < -55) Temperature = -55;
  config.baseTemp = Temperature;
  
  EEPROMWritelong(50, config.baseTemp);
  EEPROM.commit();  
}

void post_put() {
  
    if (config.enableAPI == false) {
      server.send(400);
      return;
    }
  
    StaticJsonBuffer<500> jsonBuffer;
    String post_body = server.arg("plain");
    Serial.println(post_body);

    JsonObject& jsonBody = jsonBuffer.parseObject(post_body);

    Serial.print("HTTP Method: ");
    Serial.println(server.method());
    
    if (!jsonBody.success()) {
        Serial.println("error in parsin json body");
        server.send(400);
    }
    else {   
        if (server.method() == HTTP_PUT) {
            if (jsonBody["INTERVAL"] == true) {
                json_to_interval(jsonBody);
                unsigned int duration = jsonBody["iDuration"];
                float temperature = jsonBody["iTemp"];
                server.sendHeader("Location", "/interval/" + String(temperature) + "stC/" + String(duration) + "min.");
                server.send(200);
            } else if (jsonBody["PROGRAM"]) {
                int progNumber = jsonBody["PROGRAM"];
                 
                  if (progNumber <= 0 || progNumber > 9) { // program number must be in range 1-8 or memory address selection fail
                    server.send(404);
                  } else if (progNumber == 9){     // 9 is program number for main temperature modification
                    float Temperature = jsonBody["TEMP"];
                    json_to_temperature(jsonBody);
                    server.sendHeader("Location", "/temperature/" + String(Temperature));
                    server.send(200); 
                  } else {  
                  json_to_program(jsonBody, progNumber);
                  server.sendHeader("Location", "/program/" + String(progNumber));
                  server.send(200);  
                  }            
                } else
                  server.send(404);
                  
        } else if (server.method() == HTTP_POST) {
          if (jsonBody["PROGRAM"] == "read") {
            byte progNumber = jsonBody["NUMBER"];
              if (progNumber > 8 || progNumber == 0) { // program number must be in range 1-8 or memory address selection fail
                server.send(404);
              } else {
                  server.sendHeader("Location", "/Program/" + String(progNumber));
                  post_program (progNumber);
              }
            } else 
              server.send(404);
        }
    }
}

#endif
