#include <PowerDetector.h>
#include <Arduino.h>

/**************************************************/
/**************   PowerDetector    ****************/
/**************************************************/
/*
  When the "power on" on A0 the voltage is equal VCC (5V).
  Because A0 is connected to supply voltage. Therefore, the value of A0 == ~1023.
  When the power off, the voltage on A0 becomes lower than the VCC voltage. VCC have power from capacitors.
  Therefore, the value of A0 becomes < 1000.
  It takes ~ 100ms. This is enough to save the config in EEPROM.
*/

PowerDetector::PowerDetector(unsigned char pin){
  this->pin = pin;
  pinMode(this->pin, INPUT);

  this->pinMask = digitalPinToBitMask(pin);
  this->pinPort = portInputRegister(digitalPinToPort(pin));
}

bool PowerDetector::isPowerOn(){
  //return analogRead(this->pin) >= 1020;
  //return digitalRead(this->pin) == HIGH;
  return (*this->pinPort & this->pinMask) != 0; // != LOW
}
