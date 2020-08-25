#include <Display.h>
#include <Arduino.h>

//#define IN_DEBUG_MODE

Display::Display (uint8_t pinClk, uint8_t pinDIO, float milimetersPerStep) : TM1637Display(pinClk, pinDIO){
    this->milimetersPerStep = milimetersPerStep;
    this->setBrightness(0x0a);
}

signed short int Display::getPosition(){
    return this->position;
}

bool Display::setPosition(signed short int position){
    if (this->position == position) return false;
    this->position = position;
    this->needToShow = true;
    #ifdef IN_DEBUG_MODE
    Serial.print("\n\r display value changed");
    #endif
    return true;
}

float Display::getHeightInMilimeters(){
    return this->milimetersPerStep * this->position;
}

void Display::show(){
    #ifdef IN_DEBUG_MODE
    Serial.print("\n\r show to display:"+String(this->getHeightInMilimeters(),DEC));
    #endif
    this->showFloat(this->getHeightInMilimeters(), 1);
    this->needToShow = false;
    this->updateTime = millis();
}

bool Display::update(){
    if (!this->needToShow) return false;
    if (this->updateTime + 300 > millis()) return false;
    this->show();
    return true;
}

unsigned long Display::getUpdateTime(){
    return this->updateTime;
}

bool Display::isNeedToShow(){
    return this->needToShow;
}

