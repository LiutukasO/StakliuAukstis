#include <Position.h>

Position::Position (unsigned char stepsPerRound, float milimetersPerRound, unsigned char maxMilimeters){
    this->stepsPerRound = stepsPerRound;
    this->milimetersPerRound = milimetersPerRound;
    this->maxMilimeters = maxMilimeters;

    this->milimetersPerStep = this->milimetersPerRound / this->stepsPerRound;
    this->stepsInOneMilimeter = 1 / milimetersPerStep;

    this->maxPosition = this->maxMilimeters / milimetersPerStep;
}

float Position::getMilimetersPerStep(){
    return this->milimetersPerStep;
}

signed int Position::fitPositionToValidRange(signed int position){
    if (position > this->maxPosition) return this->maxPosition;
    else if (position < 0) return 0;
    return position;
}

signed int Position::milimetersToSteps(signed int milimeters){
    return this->stepsInOneMilimeter * milimeters;
}
