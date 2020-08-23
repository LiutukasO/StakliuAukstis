#include <Stakles.h>

Stakles* stakles;

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Paleidziamos stakles!");

  const byte powerPin       = A0;
  const byte displayClkPin  = 8; // CLK D8
  const byte displayDioPin  = 7; // DIO D7
  const byte encoderPinA    = 2;
  const byte encoderPinB    = 3;
  const byte buttonTopPin   = 9;
  const byte buttonDownPin  = 10;

  const unsigned char stepsPerRound = 16;
  const float milimetersPerRound    = 0.2;
  const unsigned int maxMilimeters  = 250;

  stakles = new Stakles(
    powerPin,
    displayClkPin,
    displayDioPin,
    encoderPinA,
    encoderPinB,
    buttonTopPin,
    buttonDownPin,
    stepsPerRound,
    milimetersPerRound,
    maxMilimeters
  );

  Serial.println("\r\nStakles veikia!");
}


void loop(void)
{
  stakles->process();
}


