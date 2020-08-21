#define Position_h

#include "Arduino.h"

class Position
{
  public:
    Position (float milimetersPerRound, unsigned char stepsPerRound, unsigned int maxMilimeters);

    signed int getPosition();
    bool setPosition (signed int position);

    unsigned long getPositionTime();

    void increaseBySteps(signed int steps);
    void increaseByMilimeters(signed int milimeters);

    float getHeightInMilimeters();
    bool isChanging();

  private:

    signed int position = 0; // default position
    unsigned long positionTime = 0;

    // 8 holes * 2 sensors
    // 0011|0011|0011|0011|0011|0011|0011|0011
    // 0110|0110|0110|0110|0110|0110|0110|0110

    float milimetersPerRound = 0.2;
    unsigned char stepsPerRound = 16;
    unsigned int maxMilimeters = 250;

    float milimetersPerStep = this->milimetersPerRound / this->stepsPerRound; // 0.2mm / 16 = 0.0125mm
    float stepsInOneMilimeter = 1 / milimetersPerStep; // 1mm / 0.0125mm/step = 80 steps

    signed int maxPosition = this->maxMilimeters / milimetersPerStep; // 250 mm

};