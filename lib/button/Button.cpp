#include "Button.h"

//#define IN_DEBUG_MODE

Button::Button (){
}

Button::Button (byte pin){
    this->init(pin, 25);
}

Button::Button (byte pin, byte debounceDelay){
    this->init(pin, debounceDelay);
}

void Button::init (byte pin, byte debounceDelay){
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

byte Button::getSpeedLevel(){
    unsigned long period = millis() - this->stateChangeLastTime;
    #ifdef IN_DEBUG_MODE
    Serial.print("\n\r button period:"+String(period, DEC));
    #endif
    byte speedLevel = period / 1000;
    #ifdef IN_DEBUG_MODE
    Serial.print(" speed:"+String(speedLevel, DEC));
    #endif
    return speedLevel;
}