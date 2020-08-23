#ifndef Position_h
#define Position_h

class Position
{
  public:
    Position (unsigned char stepsPerRound, float milimetersPerRound, unsigned char maxMilimeters);
    
    float getMilimetersPerStep();
    signed short int fitPositionToValidRange(signed short int position);
    signed short int milimetersToSteps(signed short int milimeters);

  private:

    // 8 holes * 2 sensors
    // 0011|0011|0011|0011|0011|0011|0011|0011
    // 0110|0110|0110|0110|0110|0110|0110|0110

    float milimetersPerRound = 0.2;
    unsigned char stepsPerRound = 16;
    unsigned char maxMilimeters = 250;

    float milimetersPerStep = milimetersPerRound / stepsPerRound; // 0.2mm / 16 = 0.0125mm
    float stepsInOneMilimeter = 1 / milimetersPerStep; // 1mm / 0.0125mm/step = 80 steps

    signed short int maxPosition = maxMilimeters / milimetersPerStep; // max 20`000 steps

};

#endif