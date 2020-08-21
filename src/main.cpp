#define ENCODER_USE_INTERRUPTS
//#define ENCODER_OPTIMIZE_INTERRUPTS

#include "Stakles.h"

Stakles* stakles;

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Paleidziamos stakles!");

  float milimetersPerRound    = 0.2;
  unsigned char stepsPerRound = 16;
  unsigned int maxMilimeters  = 250;

  stakles = new Stakles(milimetersPerRound, stepsPerRound, maxMilimeters);
  stakles->power_init(A0);
  stakles->led_init(8, 7); // (CLK -> D8, DIO -> D7)
  stakles->encoder_init(2, 3);
  stakles->button_TOP_init(9);
  stakles->button_DOWN_init(10);
  stakles->init();

  Serial.println("\r\nStakles veikia!");
}


void loop(void)
{
  stakles->process();
}


