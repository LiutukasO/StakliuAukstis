#ifndef Stakles_h
#define Stakles_h

//#define IN_DEBUG_MODE
#define ENCODER_USE_INTERRUPTS

#include <Config.h>
#include <Display.h>
#include <Button.h>
#include <Encoder.h>
#include <Position.h>
#include <PowerDetector.h>

class Stakles
{
  public:
    Stakles (
      const byte powerPin,
      const byte displayClkPin,
      const byte displayDioPin,
      const byte encoderPinA,
      const byte encoderPinB,
      const byte buttonTopPin,
      const byte buttonBottomPin,
      const unsigned char stepsPerRound,
      const float milimetersPerRound,
      const unsigned int maxMilimeters
    );

    void process();

  private:

    // DEBUG
    unsigned long loopCount = 0;
    unsigned long debugTime = 0;
    void          debug_update();

    // POWER
    PowerDetector* powerDetector;

    // CONFIG
    Config* config;
    void config_update();

    // DISPLAY
    Display* display;

    // BUTTON
    Button button_TOP;
    Button button_DOWN;
    void button_TOP_pressed();
    void button_DOWN_pressed();
    void button_update();

    // ENCODER
    Encoder* encoder;

    Position* position;

};

#endif