#ifndef PowerDetector_h
#define PowerDetector_h

class PowerDetector
{
    public:
        PowerDetector (unsigned char pin);
        bool isPowerOn();
        
    private:
        unsigned char pin;
};

#endif