#ifndef THERMOSTAT_H
#define THERMOSTAT_H

float setTemp;              // variable stores the temperature to be kept by the thermostat.
float measureTemp;          // measured temperature

/*
   PROGRAMATOR
*/

struct strProgramData {
  byte startH;
  byte startM;
  byte stopH;
  byte stopM;
  float tempProgramu;
  bool Pn;
  bool Wt;
  bool Sr;
  bool Cz;
  bool Pt;
  bool So;
  bool Nd;
  bool Enabled;
} progData[17];

int memAdresSelection(byte progNumber) {
  int result;
  switch (progNumber) { // address selection depending on programm number
    case 1:
      result = 300;
      return result;
      break;
    case 2:
      result = 310;
      return result;
      break;
    case 3:
      result = 320;
      return result;
      break;
    case 4:
      result = 330;
      return result;
      break;
    case 5:
      result = 340;
      return result;
      break;
    case 6:
      result = 350;
      return result;
      break;
    case 7:
      result = 360;
      return result;
      break;
    case 8:
      result = 370;
      return result;
      break;
    case 9:
      result = 380;
      return result;
      break;
    case 10:
      result = 390;
      return result;
      break;
    case 11:
      result = 400;
      return result;
      break;
    case 12:
      result = 410;
      return result;
      break;
    case 13:
      result = 420;
      return result;
      break;
    case 14:
      result = 430;
      return result;
      break;
    case 15:
      result = 440;
      return result;
      break;
    case 16:
      result = 450;
      return result;
      break;
  }
}

//Program saving procedure for enableSafety

void writeProgram(byte progNo) { // numer programu
  int adress;
  adress = memAdresSelection(progNo);
  // calculation of the WEEKDAYS byte
  byte weekdays;
  bitWrite(weekdays, 0, progData[progNo].Enabled);
  bitWrite(weekdays, 1, progData[progNo].Pn);
  bitWrite(weekdays, 2, progData[progNo].Wt);
  bitWrite(weekdays, 3, progData[progNo].Sr);
  bitWrite(weekdays, 4, progData[progNo].Cz);
  bitWrite(weekdays, 5, progData[progNo].Pt);
  bitWrite(weekdays, 6, progData[progNo].So);
  bitWrite(weekdays, 7, progData[progNo].Nd);
  
  if ((!config.enableSafety && !config.enableSafetyTemp) || (!config.enableSafety && config.enableSafetyTemp)) {  // if SAFETY is DISBLED then write program to hot and cold mem banks
    EEPROM.write(adress, progData[progNo].startH);
    EEPROM.write(adress + 1, progData[progNo].startM);
    EEPROM.write(adress + 2, progData[progNo].stopH);
    EEPROM.write(adress + 3, progData[progNo].stopM);
    EEPROM.write(adress + 4, weekdays);
    EEPROMWritelong(adress + 5, progData[progNo].tempProgramu);
    adress=adress+80;
    EEPROM.write(adress, progData[progNo].startH);
    EEPROM.write(adress + 1, progData[progNo].startM);
    EEPROM.write(adress + 2, progData[progNo].stopH);
    EEPROM.write(adress + 3, progData[progNo].stopM);
    EEPROM.write(adress + 4, weekdays);
    EEPROMWritelong(adress + 5, progData[progNo].tempProgramu);
    
    progData[progNo+8].startH = progData[progNo].startH;
    progData[progNo+8].startM = progData[progNo].startM;
    progData[progNo+8].stopH = progData[progNo].stopH;
    progData[progNo+8].stopM = progData[progNo].stopM;
    progData[progNo+8].Enabled =  progData[progNo].Enabled;
    progData[progNo+8].Pn = progData[progNo].Pn;
    progData[progNo+8].Wt = progData[progNo].Wt;
    progData[progNo+8].Sr = progData[progNo].Sr;
    progData[progNo+8].Cz = progData[progNo].Cz;
    progData[progNo+8].Pt = progData[progNo].Pt;
    progData[progNo+8].So = progData[progNo].So;
    progData[progNo+8].Nd = progData[progNo].Nd;
    progData[progNo+8].tempProgramu = progData[progNo].tempProgramu;
    
  } else if (config.enableSafety && config.enableSafetyTemp) {        // if SAFETY is ENABLED then write only to COLD bank
    EEPROM.write(adress, progData[progNo].startH);
    EEPROM.write(adress + 1, progData[progNo].startM);
    EEPROM.write(adress + 2, progData[progNo].stopH);
    EEPROM.write(adress + 3, progData[progNo].stopM);
    EEPROM.write(adress + 4, weekdays);
    EEPROMWritelong(adress + 5, progData[progNo].tempProgramu);
    ledOn(); // LED ON - visual information that data are pending rewrite to hot bank
  }
  EEPROM.commit();
}

void readProgram(byte progNo) { // reading a program data into RAM
  //int x = progNo;
  int adress;
  adress = memAdresSelection(progNo);
  progData[progNo].startH = EEPROM.read(adress);
  progData[progNo].startM = EEPROM.read(adress + 1);
  progData[progNo].stopH = EEPROM.read(adress + 2);
  progData[progNo].stopM = EEPROM.read(adress + 3);

  byte weekdays;
  weekdays = EEPROM.read(adress + 4);           // wczytanie bajtu do zmiennej weekdays
  progData[progNo].Enabled = bitRead(weekdays, 0);
  progData[progNo].Pn = bitRead(weekdays, 1);
  progData[progNo].Wt = bitRead(weekdays, 2);
  progData[progNo].Sr = bitRead(weekdays, 3);
  progData[progNo].Cz = bitRead(weekdays, 4);
  progData[progNo].Pt = bitRead(weekdays, 5);
  progData[progNo].So = bitRead(weekdays, 6);
  progData[progNo].Nd = bitRead(weekdays, 7);
  progData[progNo].tempProgramu = EEPROMReadlong(adress + 5);
}

void reWrite() { //the procedure for rewriting values from thermostat cold bank to thermostat hot bank
  for (int progNo = 9; progNo <= 16; progNo++) {
    
    //Copying data from cold programs to hot programs
    
    progData[progNo-8].startH = progData[progNo].startH;
    progData[progNo-8].startM = progData[progNo].startM;
    progData[progNo-8].stopH = progData[progNo].stopH;
    progData[progNo-8].stopM = progData[progNo].stopM;
    progData[progNo-8].Enabled =  progData[progNo].Enabled;
    progData[progNo-8].Pn = progData[progNo].Pn;
    progData[progNo-8].Wt = progData[progNo].Wt;
    progData[progNo-8].Sr = progData[progNo].Sr;
    progData[progNo-8].Cz = progData[progNo].Cz;
    progData[progNo-8].Pt = progData[progNo].Pt;
    progData[progNo-8].So = progData[progNo].So;
    progData[progNo-8].Nd = progData[progNo].Nd;
    progData[progNo-8].tempProgramu = progData[progNo].tempProgramu;
    }         
    //writing data from hot programs to hot memory
  for (int progNo = 1; progNo <= 8; progNo++) {
    int adress;
    adress = memAdresSelection(progNo);
     // calculation of the WEEKDAYS byte
    byte weekdays;
    bitWrite(weekdays, 0, progData[progNo].Enabled);
    bitWrite(weekdays, 1, progData[progNo].Pn);
    bitWrite(weekdays, 2, progData[progNo].Wt);
    bitWrite(weekdays, 3, progData[progNo].Sr);
    bitWrite(weekdays, 4, progData[progNo].Cz);
    bitWrite(weekdays, 5, progData[progNo].Pt);
    bitWrite(weekdays, 6, progData[progNo].So);
    bitWrite(weekdays, 7, progData[progNo].Nd);
    
    EEPROM.write(adress, progData[progNo].startH);
    EEPROM.write(adress + 1, progData[progNo].startM);
    EEPROM.write(adress + 2, progData[progNo].stopH);
    EEPROM.write(adress + 3, progData[progNo].stopM);
    EEPROM.write(adress + 4, weekdays);
    EEPROMWritelong(adress + 5, progData[progNo].tempProgramu);
    ledOff(); // LED OFF - visual information that data are rewriten
  }
    EEPROM.commit();
}

/* 
If the end time of a program is 00:00 then change the time to 23:59
*/
void midnightCheck (byte progNumber){
    if (progData[progNumber].stopH == 0 && progData[progNumber].stopM == 0){
      progData[progNumber].stopH = 23;
      progData[progNumber].stopM = 59;
    }
}

/*
   Function finds programmed temperature
   If there is no programm for the current (epoch) time
   it takes the basic temperature set on page_GENERAL
*/

float checkProgTemp (void)
{
  byte wDay = DateTime.wday;

  if (intervalMode){               //if interval mode is enabled return the temperature set on the interval page. Exit.
    programFit = 10;
    return intervalTemperature;
  } else if (firstStart == true){
    programFit = 0;
    return config.baseTemp;
  }
  
  for (byte progNo = 1; progNo <= 8; progNo++)
  {
    epochSTARTminuty = epochDays * 1440 + progData[progNo].startH * 60 + progData[progNo].startM;
    epochSTOPminuty = epochDays * 1440 + progData[progNo].stopH * 60 + progData[progNo].stopM;

    if (epochMinutes >= epochSTARTminuty && epochMinutes <= epochSTOPminuty  && progData[progNo].Enabled == true) // the range is checked only for enabled programms
    {
      if (wDay == 1 && progData[progNo].Nd == true || wDay == 2 && progData[progNo].Pn == true || wDay == 3 && progData[progNo].Wt == true || wDay == 4 && progData[progNo].Sr == true || wDay == 5 && progData[progNo].Cz == true || wDay == 6 && progData[progNo].Pt == true || wDay == 7 && progData[progNo].So == true)
      { // the program temperature is returned only if the week day is set in the program
        programFit = progNo;
        /*
        Serial.print ("Program fit: ");
        Serial.print (progNo);
        Serial.print (", temp: ");
        Serial.println (progData[progNo].tempProgramu);
        */
        return progData[progNo].tempProgramu;
      }
    }
  }
  programFit = 0;
  return config.baseTemp; // If no active and valid program data are matching cuttent day and time, return the basic temperature.
}


void firstStartGeneralConfig (){
    config.ssid = "ssid";
    config.password = "hasło";
    config.dhcp = true;
    config.IP[0] = 192; config.IP[1] = 168; config.IP[2] = 4; config.IP[3] = 1;
    config.Netmask[0] = 255; config.Netmask[1] = 255; config.Netmask[2] = 255; config.Netmask[3] = 0;
    config.Gateway[0] = 192; config.Gateway[1] = 168; config.Gateway[2] = 1; config.Gateway[3] = 1;
    config.ntpServerName = "0.pl.pool.ntp.org";
    config.Update_Time_Via_NTP_Every = 120;
    config.timezone = 10;
    config.daylight = true;
    config.DeviceName = "Termostat";
    config.DeviceNumber = 0;
    config.baseTemp = 20;
    config.ds_resolution = 12;
    config.enableThingspeak = false;
    config.hostServerName = "api.thingspeak.com";
    config.hostUpdatePeriod = 15;
    config.hostChannelNumber = 0;
    config.hostWriteKey = "key";
    config.enableSafety = false;
    config.enableSafetyTemp = false;
    config.enableAPI = false;
    config.coolMode = false;

    config.histeresisUpper = 0.3;
    config.histeresisLower = 0.3;
}


void firstStartProgramConfig (){   // default program configuration @first start
      progData[1].startH = 0;
      progData[1].startM = 0;
      progData[1].stopH = 4;
      progData[1].stopM = 0;
      progData[1].tempProgramu = 20;
      progData[1].Pn = true;
      progData[1].Wt = true;
      progData[1].Sr = true;
      progData[1].Cz = true;
      progData[1].Pt = true;
      progData[1].So = true;
      progData[1].Nd = true;
      progData[1].Enabled = false;
      writeProgram(1);
      progData[2].startH = 4;
      progData[2].startM = 0;
      progData[2].stopH = 6;
      progData[2].stopM = 0;
      progData[2].tempProgramu = 22;
      progData[2].Pn = true;
      progData[2].Wt = true;
      progData[2].Sr = true;
      progData[2].Cz = true;
      progData[2].Pt = true;
      progData[2].So = true;
      progData[2].Nd = true;
      progData[2].Enabled = false;
      writeProgram(2);
      progData[3].startH = 6;
      progData[3].startM = 0;
      progData[3].stopH = 13;
      progData[3].stopM = 0;
      progData[3].tempProgramu = 19;
      progData[3].Pn = true;
      progData[3].Wt = true;
      progData[3].Sr = true;
      progData[3].Cz = true;
      progData[3].Pt = true;
      progData[3].So = true;
      progData[3].Nd = true;
      progData[3].Enabled = false;
      writeProgram(3);
      progData[4].startH = 13;
      progData[4].startM = 0;
      progData[4].stopH = 15;
      progData[4].stopM = 0;
      progData[4].tempProgramu = 22;
      progData[4].Pn = true;
      progData[4].Wt = true;
      progData[4].Sr = true;
      progData[4].Cz = true;
      progData[4].Pt = true;
      progData[4].So = true;
      progData[4].Nd = true;
      progData[4].Enabled = false;
      writeProgram(4);
      progData[5].startH = 15;
      progData[5].startM = 0;
      progData[5].stopH = 18;
      progData[5].stopM = 0;
      progData[5].tempProgramu = 20;
      progData[5].Pn = true;
      progData[5].Wt = true;
      progData[5].Sr = true;
      progData[5].Cz = true;
      progData[5].Pt = true;
      progData[5].So = true;
      progData[5].Nd = true;
      progData[5].Enabled = false;
      writeProgram(5);
      progData[6].startH = 18;
      progData[6].startM = 0;
      progData[6].stopH = 22;
      progData[6].stopM = 0;
      progData[6].tempProgramu = 22;
      progData[6].Pn = true;
      progData[6].Wt = true;
      progData[6].Sr = true;
      progData[6].Cz = true;
      progData[6].Pt = true;
      progData[6].So = true;
      progData[6].Nd = true;
      progData[6].Enabled = false;
      writeProgram(6);
      progData[7].startH = 22;
      progData[7].startM = 0;
      progData[7].stopH = 23;
      progData[7].stopM = 59;
      progData[7].tempProgramu = 21;
      progData[7].Pn = true;
      progData[7].Wt = true;
      progData[7].Sr = true;
      progData[7].Cz = true;
      progData[7].Pt = true;
      progData[7].So = true;
      progData[7].Nd = true;
      progData[7].Enabled = false;
      writeProgram(7);
      progData[8].startH = 0;
      progData[8].startM = 0;
      progData[8].stopH = 23;
      progData[8].stopM = 59;
      progData[8].tempProgramu = 18;
      progData[8].Pn = true; 
      progData[8].Wt = true;
      progData[8].Sr = true;
      progData[8].Cz = true;
      progData[8].Pt = true;
      progData[8].So = true;
      progData[8].Nd = true;
      progData[8].Enabled = false;
      writeProgram(8);
}

#endif
