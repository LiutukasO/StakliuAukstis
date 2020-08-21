#include "Config.h"
#include "Arduino.h"
#include <EEPROM.h>

/**************************************************/
/****************   CONFIG    *********************/
/**************************************************/

Config::Config(){
  this->load();
}

bool Config::load() {
  this->configTime = millis();
  this->sizeInBytes = sizeof(this->config);
  //EEPROM.begin(4096);
  if (Serial) {
      Serial.print("\n\r Config size:"+String(this->sizeInBytes));
      Serial.print("\n\r Config version:["+String(configVersion)+"]?["+char(EEPROM.read(readFromByte + 0))+char(EEPROM.read(readFromByte + 1))+char(EEPROM.read(readFromByte + 2))+char(EEPROM.read(readFromByte + 3))+char(EEPROM.read(readFromByte + 4))+char(EEPROM.read(readFromByte + 5))+"]");
  }
  if (EEPROM.read(readFromByte + 0) == configVersion[0] &&
      EEPROM.read(readFromByte + 1) == configVersion[1] &&
      EEPROM.read(readFromByte + 2) == configVersion[2] &&
      EEPROM.read(readFromByte + 3) == configVersion[3] &&
      EEPROM.read(readFromByte + 4) == configVersion[4] &&
      EEPROM.read(readFromByte + 5) == configVersion[5]
      ){
      do {
        if (this->config.writeCounter == 65535) {
          if (Serial) Serial.print("\n\r EEPROM data block: "+String(readFromByte,DEC)+" used maximum, read from next EEPROM block.");
          readFromByte += this->sizeInBytes;
        }
        EEPROM.get(readFromByte, this->config);
      } while (this->config.writeCounter == 65535);
      if (Serial) Serial.print("\n\r EEPROM data block: "+String(readFromByte,DEC)+" how many times used: "+String(this->config.writeCounter, DEC));
  } else {
    this->save();
  }
  if (Serial && this->debug) this->print();
  EEPROM.end();
  this->saved = true;
  return true;
}


bool Config::save(){
  if (this->isConfigSaved()) return true;
  this->configTime = millis();
  //EEPROM.begin(4096);
  this->config.writeCounter++;
  if (this->config.writeCounter < 65535) EEPROM.put(readFromByte, this->config);
  else {
    EEPROM.put(readFromByte, this->config);
    readFromByte += sizeof(this->config);
    this->config.writeCounter = 1;
    EEPROM.put(readFromByte, this->config);
  }
  //EEPROM.commit();
  if (this->debug && Serial) Serial.print("\n\r Config Saved successfully!");
  EEPROM.end();
  this->saved = true;
  return true;
}


void Config::print(){
  if (!Serial) return;
  Serial.print("\n\r Config:["+String(this->config.version)+"]");
  Serial.print("\n\r WiFi ssid:["+String(this->config.wifi_ssid)+"], pass:["+String(this->config.wifi_pass)+"], port:["+String(this->config.wifi_port)+"]");
  Serial.print("\n\r API URL:["+String(this->config.api_host)+":"+String(this->config.api_port)+"], token:["+String(this->config.api_token)+"]");
  Serial.print("\n\r Height:["+String(this->config.height)+"]");
  Serial.print("\n\r");
}

unsigned long Config::getConfigTime() {
  return this->configTime;
}

bool Config::isConfigSaved(){
  return this->saved;
}

void Config::setHeight(float position){
  if (this->config.height == position) return; 
  this->config.height = position;
  this->saved = false;
}

float Config::getHeight(){
  return this->config.height;
}