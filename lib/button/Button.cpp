#include "Button.h"
#include "Arduino.h"

Button::Button (){
}

Button::Button (uint8_t pin){
    this->init(pin, 25);
}

Button::Button (uint8_t pin, unsigned int debounceDelay){
    this->init(pin, debounceDelay);
}

void Button::init (uint8_t pin, unsigned int debounceDelay){
  pinMode(pin,  INPUT_PULLUP);
  this->attach(pin);
  this->interval(debounceDelay);
}

bool Button::isPressed(){
    this->update();
    return (this->read() == LOW);
}

unsigned long Button::getStateTime(){
    return this->duration();
}

unsigned int Button::getSpeedLevel(){
    unsigned long period = millis() - this->stateChangeLastTime;
    unsigned int speedLevel = (int) period / 1000;
    return speedLevel;
}