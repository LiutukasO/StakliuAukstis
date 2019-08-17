#include "Config.h"
#include "Arduino.h"
#include <EEPROM.h>

/**************************************************/
/****************   CONFIG    *********************/
/**************************************************/

Config::Config (){
  this->load();
}

bool Config::load() {
  this->config_time = millis();
  this->CONFIG_SIZE = sizeof(this);
  //EEPROM.begin(4096);
  if (Serial) {
      Serial.print("\n\r Config size:"+String(this->CONFIG_SIZE));
      Serial.print("\n\r Config version:["+String(CONFIG_VERSION)+"]?["+char(EEPROM.read(CONFIG_START + 0))+char(EEPROM.read(CONFIG_START + 1))+char(EEPROM.read(CONFIG_START + 2))+char(EEPROM.read(CONFIG_START + 3))+char(EEPROM.read(CONFIG_START + 4))+char(EEPROM.read(CONFIG_START + 5))+"]");
  }
  if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
      EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
      EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2] &&
      EEPROM.read(CONFIG_START + 3) == CONFIG_VERSION[3] &&
      EEPROM.read(CONFIG_START + 4) == CONFIG_VERSION[4] &&
      EEPROM.read(CONFIG_START + 5) == CONFIG_VERSION[5]
      ){
      do {
        if (this->config.write_counter == 65535) CONFIG_START += this->CONFIG_SIZE;
        EEPROM.get(CONFIG_START, this->config);          
      } while (this->config.write_counter == 65535);
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
  this->config_time = millis();
  //EEPROM.begin(4096);
  this->config.write_counter++;
  if (this->config.write_counter < 65535) EEPROM.put(CONFIG_START, this->config);
  else {
    EEPROM.put(CONFIG_START, this->config);
    CONFIG_START += sizeof(this->config);
    this->config.write_counter = 1;
    EEPROM.put(CONFIG_START, this->config);
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
  return this->config_time;
}

bool Config::isConfigSaved(){
  return this->saved;
}

void Config::setHeight(unsigned int height){
  if (this->config.height == height) return; 
  this->config.height = height;
  this->saved = false;
}

unsigned int Config::getHeight(){
  return this->config.height;
}