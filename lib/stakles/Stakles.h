#define Stakles_h

#include <Config.h>
#include <TM1637Display.h>
#include <Button.h>
#include <Encoder.h>

class Stakles
{
  public:
    Stakles ();
    bool debug = false;

    void init();
    void process();

    // POWER
    uint8_t power_port;
    void power_init(uint8_t pin);
    bool is_power_on();

    // LED
    void led_init(uint8_t CLK, uint8_t DIO);

    // BUTTON
    void button_L_init(uint8_t pin);
    void button_R_init(uint8_t pin);

    // ENCODER
    void encoder_init(uint8_t l_pin, uint8_t r_pin);

    // MOVE
    void move_to_l ();
    void move_to_r ();
    void set_height  (uint32_t height);
    float get_height();
    float get_height(uint32_t height);

  private:
    unsigned long int height = 320; // 40mm 

    // DEBUG
    unsigned long debug_time = 0;
    bool          debug_update();
    unsigned long count_x = 0;

    // POWER
    uint8_t power_pin;

    // CONFIG
    Config config;
    bool config_update();

    // LED
    TM1637Display led;
    bool led_update();

    // ENCODER
    Encoder* encoder;
    unsigned long encoder_time = 0;
    bool encoder_update();

    // BUTTON
    int debounceDelay = 10; //ms
    Button button_L;
    Button button_R;
    bool button_L_pressed();
    bool button_R_pressed();
    bool button_update();

    // MOVE
    const float        delta_360 = 0.2; //mm
    const unsigned int steps_per_round = 16; // 8 skyles * 2 sensoriai  
    const float        delta_step = this->delta_360 / this->steps_per_round;

};