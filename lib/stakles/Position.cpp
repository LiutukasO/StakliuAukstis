
#include "Position.h"

Position::Position (float milimetersPerRound, unsigned char stepsPerRound, unsigned int maxMilimeters){
    this->milimetersPerRound = milimetersPerRound; // 0.2mm
    this->stepsPerRound = stepsPerRound; // 16
    this->maxMilimeters = maxMilimeters; // 250mm
    
    this->milimetersPerStep = this->milimetersPerRound / this->stepsPerRound; // 0.2mm / 16 = 0.0125mm
    this->stepsInOneMilimeter = 1 / milimetersPerStep; // 1mm / 0.0125mm/step = 80 steps

    this->maxPosition = this->maxMilimeters / milimetersPerStep; // = 250 mm
}

signed int Position::getPosition(){
    return this->position;
}

bool Position::setPosition(signed int position){
    if (this->position == position) return false;
    if (position > maxPosition) position = maxPosition;
    else if (position < 0) position = 0;
    this->positionTime = millis();
    this->position = position;
    return true;
}

unsigned long Position::getPositionTime(){
    return this->positionTime;
}

void Position::increaseBySteps(signed int steps){
    this->setPosition(this->position + steps);
}

void Position::increaseByMilimeters(signed int milimeters){
    int steps = stepsInOneMilimeter * milimeters;
    this->setPosition(this->position + steps);
}

float Position::getHeightInMilimeters(){
    return (float) round((float)this->milimetersPerStep * this->position *10)/10;
}

bool Position::isChanging(){
    return this->positionTime + 300 > millis();
}

