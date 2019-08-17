#include "Stakles.h"
#include <EEPROM.h>

Stakles::Stakles (){
  this->debug_time = millis();
  this->config = Config();
  this->height = this->config.getHeight();
}

/**************************************************/
/****************   POWER    **********************/
/**************************************************/

void Stakles::power_init(uint8_t pin){
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
  if (this->encoder_time+2000 > millis()) return false;
  if (this->config.getConfigTime()+2000 > millis()) return false;
  if (this->height == this->config.getHeight()) return false;
  if (this->is_power_on()) return false;
  this->config.setHeight(this->height);
  return this->config.save();
}

/**************************************************/
/****************    LED   ************************/
/**************************************************/

void Stakles::led_init(uint8_t CLK, uint8_t DIO){
  this->led = TM1637Display(CLK, DIO);
  this->led.setBrightness(0x0a);
  this->led_update();
}

bool Stakles::led_update(){
  if (this->led.update_time + 300 > millis()) return false;
  float tmp_height = this->get_height();
  if (tmp_height == this->led.getValue()) return false;
  if (this->debug) Serial.print("\n"+String(this->height, DEC)+" LED OLD:["+String(this->led.getValue(), DEC)+"] NEW:["+String(tmp_height, DEC)+"]");
  this->led.showFloat(tmp_height, 1);
  return true;
}

/**************************************************/
/****************   BUTTON    *********************/
/**************************************************/

void Stakles::button_L_init (uint8_t pin){
  this->button_L = Button(pin, debounceDelay);
}

void Stakles::button_R_init (uint8_t pin){
  this->button_R = Button(pin, debounceDelay);
}

bool Stakles::button_L_pressed(){
  if (this->encoder_time + 300 > millis()) return false;
  //if (this->debug) Serial.print("\nbutton_L_pressed A:"+String(this->height));
  if      (this->button_L.getSpeedLevel() <= 1) this->height++;
  if      (this->button_L.getSpeedLevel() <= 3) this->height += this->steps_per_round/4;
  else if (this->button_L.getSpeedLevel() <= 5) this->height += this->steps_per_round/2;
  else if (this->button_L.getSpeedLevel() <= 9) this->height += this->steps_per_round*1;
  else                                          this->height += this->steps_per_round*10;
  this->encoder->write(this->height);
  this->encoder_time = millis();
  //if (this->debug) Serial.print("\nbutton_L_pressed A:"+String(this->height));
  return true;
}

bool Stakles::button_R_pressed(){
  if (this->encoder_time + 300 > millis()) return false;
  //if (this->debug) Serial.print("\nbutton_R_pressed A:"+String(this->height));
  if      (this->button_R.getSpeedLevel() <= 1) this->height--;
  if      (this->button_R.getSpeedLevel() <= 3) this->height -= this->steps_per_round/4;
  else if (this->button_R.getSpeedLevel() <= 5) this->height -= this->steps_per_round/2;
  else if (this->button_R.getSpeedLevel() <= 9) this->height -= this->steps_per_round;
  else                                          this->height -= this->steps_per_round*10;
  this->encoder->write(this->height);
  this->encoder_time = millis();
  //if (this->debug) Serial.print("\nbutton_R_pressed A:"+String(this->height));
  return true;
}

bool Stakles::button_update(){
  if (this->button_L.isPressed()) this->button_L_pressed();
  if (this->button_R.isPressed()) this->button_R_pressed();
  return true;
}


/**************************************************/
/****************   ENCODER    ********************/
/**************************************************/


void Stakles::encoder_init(uint8_t l_pin, uint8_t r_pin){
  this->encoder = new Encoder(l_pin, r_pin);
  this->encoder->write(this->height);
}

bool Stakles::encoder_update(){
  if (this->height == this->encoder->read()) return false;
  this->height = this->encoder->read();
  this->encoder_time = millis();
  return true;
}


/**************************************************/
/****************   MOVE   ************************/
/**************************************************/

void Stakles::set_height(uint32_t height){
  this->height = height;
}

float Stakles::get_height(){
  return (float) round((float)this->delta_step * this->height *10)/10;
}

float Stakles::get_height(uint32_t height){
  return (float) round((float)this->delta_step * height *10)/10;
}

/**************************************************/
/****************   DEBUG    **********************/
/**************************************************/

bool Stakles::debug_update(){
  if (this->debug_time + 10000 > millis()) return false;
  this->debug_time = millis();
  Serial.print("\n\rB:["+String(this->button_L.read())+String(this->button_R.read())+"] A:"+String(this->height, DEC) + " AG:"+String(this->get_height(), DEC) + " x:"+ String(this->count_x) + " V:"+String(analogRead(A0)));
  this->count_x = 0;
  return true;
}

/**************************************************/
/****************   LOOP   ************************/
/**************************************************/

void Stakles::process(){
  if (this->debug) this->count_x += 1;
  this->encoder_update();
  this->led_update();
  if (this->encoder_time + 300 > millis()) return;
  this->button_update();
  this->config_update();
  this->debug_update();
}

