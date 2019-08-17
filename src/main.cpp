#define ENCODER_USE_INTERRUPTS
//#define ENCODER_OPTIMIZE_INTERRUPTS

#include "Stakles.h"

Stakles stakles;

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Paleidziamos stakles!");

  stakles.debug = true;
  stakles.power_init(A0);
  stakles.led_init(8, 7); // (CLK -> D8, DIO -> D7)
  stakles.encoder_init(2, 3);
  stakles.button_L_init(9);
  stakles.button_R_init(10);

  Serial.println("Stakles veikia!");
}


void loop(void)
{
  stakles.process();
}


