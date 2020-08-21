#include "Stakles.h"

Stakles::Stakles (float milimetersPerRound, unsigned char stepsPerRound, unsigned int maxMilimeters){
  this->debug_time = millis();
  this->position = new Position(milimetersPerRound, stepsPerRound, maxMilimeters);
}

void Stakles::init(){
  this->config = new Config();
  this->position->setPosition(this->config->getHeight());
}


/**************************************************/
/****************   POWER    **********************/
/**************************************************/

void Stakles::power_init(byte pin){
  this->power_pin = pin;
  pinMode(this->power_pin, INPUT);
}

bool Stakles::is_power_on(){
  if (analogRead(this->power_pin) == 1023){
    return false;
  }
  return true;
}

/**************************************************/
/****************   CONFIG    *********************/
/**************************************************/

bool Stakles::config_update(){
  if (this->position->getPositionTime()+2000 > millis()) return false;
  if (this->config->getConfigTime()+2000 > millis()) return false;
  if (this->position->getHeightInMilimeters() == this->config->getHeight()) return false;
  if (this->is_power_on()) return false;
  this->config->setHeight(this->position->getHeightInMilimeters());
  return this->config->save();
}

/**************************************************/
/****************    LED   ************************/
/**************************************************/

void Stakles::led_init(byte CLK, byte DIO){
  this->led = TM1637Display(CLK, DIO);
  this->led.setBrightness(0x0a);
  this->led_update();
}

bool Stakles::led_update(){
  if (this->led.update_time + 300 > millis()) return false;
  float height_in_mm = this->position->getHeightInMilimeters();
  if (height_in_mm == this->led.getValue()) return false;
  this->led.showFloat(height_in_mm, 1);
  this->led.update_time = millis();
  return true;
}

/**************************************************/
/****************   BUTTON    *********************/
/**************************************************/

void Stakles::button_TOP_init (byte pin){
  this->button_TOP = Button(pin);
}

void Stakles::button_DOWN_init (byte pin){
  this->button_DOWN = Button(pin);
}

bool Stakles::button_TOP_pressed(){
  if (this->position->isChanging()) return false;
  if      (this->button_TOP.getSpeedLevel() <= 1) this->position->increaseBySteps(1);
  else if (this->button_TOP.getSpeedLevel() <= 3) this->position->increaseByMilimeters(1);
  else if (this->button_TOP.getSpeedLevel() <= 5) this->position->increaseByMilimeters(2);
  else if (this->button_TOP.getSpeedLevel() <= 9) this->position->increaseByMilimeters(3);
  else                                            this->position->increaseByMilimeters(5);
  this->encoder->write(this->position->getPosition());
  return true;
}

bool Stakles::button_DOWN_pressed(){
  if (this->position->isChanging()) return false;
  if      (this->button_DOWN.getSpeedLevel() <= 1) this->position->increaseBySteps(-1);
  else if (this->button_DOWN.getSpeedLevel() <= 3) this->position->increaseByMilimeters(-1);
  else if (this->button_DOWN.getSpeedLevel() <= 5) this->position->increaseByMilimeters(-2);
  else if (this->button_DOWN.getSpeedLevel() <= 9) this->position->increaseByMilimeters(-3);
  else                                             this->position->increaseByMilimeters(-5);
  this->encoder->write(this->position->getPosition());
  return true;
}

bool Stakles::button_update(){
  if (this->button_TOP.isPressed()) this->button_TOP_pressed();
  if (this->button_DOWN.isPressed()) this->button_DOWN_pressed();
  return true;
}


/**************************************************/
/****************   ENCODER    ********************/
/**************************************************/


void Stakles::encoder_init(byte l_pin, byte r_pin){
  this->encoder = new Encoder(l_pin, r_pin);
  this->encoder->write(this->position->getPosition());
}

bool Stakles::encoder_update(){
  return this->position->setPosition(this->encoder->read());
}


/**************************************************/
/****************   DEBUG    **********************/
/**************************************************/

bool Stakles::debug_update(){
  if (this->debug_time + 10000 > millis()) return false;
  this->debug_time = millis();
  Serial.print("\n\rB:["+String(this->button_TOP.read())+String(this->button_DOWN.read())+"]");
  Serial.print(" position:"+String(this->position->getPosition(), DEC));
  Serial.print(" height:"+String(this->position->getHeightInMilimeters(), DEC));
  Serial.print(" loopCount:"+ String(this->loopCount, DEC) + " in 10s");
  Serial.print(" power:"+String(analogRead(A0), DEC));
  this->loopCount = 0;
  return true;
}

/**************************************************/
/****************   LOOP   ************************/
/**************************************************/

void Stakles::process(){
  if (this->debug) this->loopCount++;
  if (this->led_update()) return;
  if (this->encoder_update()) return;
  this->button_update();
  this->config_update();
  this->debug_update();
}

