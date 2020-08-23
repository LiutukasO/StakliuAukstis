#ifndef Display_h
#define Display_h

#include <TM1637Display.h>

class Display : public TM1637Display
{
  public:
    Display(uint8_t pinClk, uint8_t pinDIO, float milimetersPerStep);

    signed short int getPosition();
    bool setPosition(signed short int position);
    float getHeightInMilimeters();

    bool update();

    unsigned long getUpdateTime();
    bool isNeedToShow();

  private:
    signed int position = 0;
    float milimetersPerStep;

    unsigned long updateTime = 0;
    bool needToShow = false;

    void show();

};

#endif