#ifndef PowerDetector_h
#define PowerDetector_h

class PowerDetector
{
    public:
        PowerDetector (unsigned char pin);
        bool isPowerOn();
        
    private:
        unsigned char pin;
      
        unsigned char pinMask;
        #if defined(ARDUINO_ARCH_ESP32)
        volatile unsigned int *pinPort;
        #else
        volatile unsigned char *pinPort;
        #endif

};

#endif