#define Stakles_h

#include <Config.h>
#include <TM1637Display.h>
#include <Button.h>
#include <Encoder.h>
#include <Position.h>

class Stakles
{
  public:
    Stakles (float milimetersPerRound, unsigned char stepsPerRound, unsigned int maxMilimeters);
    bool debug = true;

    void init();
    void process();

    // POWER
    byte power_port;
    void power_init(byte pin);
    bool is_power_on();

    // LED
    void led_init(byte CLK, byte DIO);

    // BUTTON
    void button_TOP_init(byte pin);
    void button_DOWN_init(byte pin);

    // ENCODER
    void encoder_init(byte l_pin, byte r_pin);

    // MOVE
    void move_to_top ();
    void move_to_down ();

  private:

    // DEBUG
    unsigned long debug_time = 0;
    bool          debug_update();
    unsigned long loopCount = 0;

    // POWER
    byte power_pin;

    // CONFIG
    Config* config;
    bool config_update();

    // LED
    TM1637Display led;
    bool led_update();

    // BUTTON
    Button button_TOP;
    Button button_DOWN;
    bool button_TOP_pressed();
    bool button_DOWN_pressed();
    bool button_update();

    // ENCODER
    Encoder* encoder;
    bool encoder_update();

    Position* position;


};