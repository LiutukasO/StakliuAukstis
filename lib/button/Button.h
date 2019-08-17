#include "Bounce2.h"

class Button : public Bounce
{
    public:
        Button ();
        Button (byte pin);
        Button (byte pin, byte debounceDelay);

        void init(byte pin, byte debounceDelay);
        bool isPressed();
        unsigned long getStateTime();
        byte getSpeedLevel();
};