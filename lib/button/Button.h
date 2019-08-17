#include "Bounce2.h"
#include "Arduino.h"

class Button : public Bounce
{
    public:
        Button ();
        Button (uint8_t pin);
        Button (uint8_t pin, unsigned int debounceDelay);

        void init(uint8_t pin, unsigned int debounceDelay);
        bool isPressed();
        unsigned long getStateTime();
        unsigned int getSpeedLevel();
};