#include <Config.h>
#include <Arduino.h>
#include <EEPROM.h>

/**************************************************/
/****************   CONFIG    *********************/
/**************************************************/

Config::Config(){
  this->load();
}

Config::Config(unsigned short maxWriteCount){
  this->maxWriteCount = maxWriteCount;
  this->load();
}

bool Config::setPosition(signed int position){
  if (this->config.position == position) return !this->saved;
  #ifdef IN_DEBUG_MODE
  Serial.print("\n\r set config position:"+String(position, DEC));
  #endif
  this->config.position = position;
  this->saved = false;
  return true;
}

signed int Config::getPosition(){
  return this->config.position;
}

unsigned short Config::getWriteCounter(){
  return this->config.writeCounter;
}

unsigned short Config::getReadFromByte(){
  return this->readFromByte;
}

void Config::print(){
  if (!Serial) return;
  Serial.print("\n\r Config version:["+String(this->config.version)+"]");
  Serial.print("\n\r writeCount:["+String(this->config.writeCounter)+"]");
  Serial.print("\n\r max writeCount:["+String(this->maxWriteCount)+"]");
  Serial.print("\n\r position:["+String(this->config.position)+"]");
  Serial.print("\n\r");
}

bool Config::isValidSecondConfig(unsigned short readFromByte){
  if (EEPROM.read(readFromByte + 0) != this->configVersion[0]) return false;
  if (EEPROM.read(readFromByte + 1) != this->configVersion[1]) return false;
  if (EEPROM.read(readFromByte + 2) != this->configVersion[2]) return false;
  if (EEPROM.read(readFromByte + 3) != this->configVersion[3]) return false;
  if (EEPROM.read(readFromByte + 4) != this->configVersion[4]) return false;
  if (EEPROM.read(readFromByte + 5) != this->configVersion[5]) return false;
  return true;
}

bool Config::load() {
  if (Serial) {
      Serial.print("\n\r max writeCount:"+String(this->maxWriteCount));
      Serial.print("\n\r Config size:"+String(this->sizeInBytes));
      Serial.print("\n\r Compare versions:["+String(this->configVersion)+"]?["+char(EEPROM.read(this->readFromByte + 0))+char(EEPROM.read(this->readFromByte + 1))+char(EEPROM.read(this->readFromByte + 2))+char(EEPROM.read(this->readFromByte + 3))+char(EEPROM.read(this->readFromByte + 4))+char(EEPROM.read(this->readFromByte + 5))+"]");
  }
  bool configLoaded = false;
  while (isValidSecondConfig(this->readFromByte)) {
    if (Serial) Serial.print("\n\r Reading config from EEPROM byte:"+String(this->readFromByte,DEC));
    EEPROM.get(this->readFromByte, this->config);
    configLoaded = true;
    if (this->config.writeCounter == this->maxWriteCount) {
      if (Serial) Serial.print("\n\r This EEPROM data block: "+String(this->readFromByte,DEC)+" has already been used max times, try to read from next EEPROM block.");
    }
    this->readFromByte += this->sizeInBytes;
  };

  if (configLoaded){
    this->readFromByte -= this->sizeInBytes;
    if (Serial) Serial.print("\n\r Loaded config from EEPROM data block:"+String(this->readFromByte,DEC));
  } else {
    if (Serial) Serial.print("\n\r Start writing default config to EEPROM.");
    this->save();
  }

  if (Serial) this->print();

  EEPROM.end();
  this->saved = true;
  return true;
}


bool Config::save(){
  if (this->saved) return true;
  this->config.writeCounter++;
  if (this->config.writeCounter <= this->maxWriteCount) EEPROM.put(this->readFromByte, this->config);
  else {
    this->readFromByte += this->sizeInBytes;
    this->config.writeCounter = 1;
    EEPROM.put(this->readFromByte, this->config);
  }
  EEPROM.end();
  this->saved = true;
  if (Serial) Serial.print("\n\r Config Saved successfully in EEPROM data block:"+String(this->readFromByte,DEC)+" with position:"+String(this->config.position));
  return true;
}
