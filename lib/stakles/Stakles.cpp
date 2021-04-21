#include <Stakles.h>

//#define IN_DEBUG_MODE

Stakles::Stakles (
      const byte powerPin,
      const byte displayCLK,
      const byte displayDIO,
      const byte encoderPinA,
      const byte encoderPinB,
      const byte buttonTopPin,
      const byte buttonDownPin,
      const unsigned char stepsPerRound,
      const float milimetersPerRound,
      const unsigned int maxMilimeters  
){
  this->debugTime = millis();
  this->powerDetector = new PowerDetector(powerPin);
  this->position = new Position(stepsPerRound, milimetersPerRound, maxMilimeters);
  this->display = new Display(displayCLK, displayDIO, this->position->getMilimetersPerStep());
  this->button_TOP = StakliuAukstis::Button(buttonTopPin);
  this->button_DOWN = StakliuAukstis::Button(buttonDownPin);
  this->config = new Config();
  this->encoder = new Encoder(encoderPinA, encoderPinB);
  this->encoder->write(this->position->fitPositionToValidRange(this->config->getPosition()));
}

/**************************************************/
/****************   CONFIG    *********************/
/**************************************************/

void Stakles::config_update(){
  //if (this->powerDetector->isPowerOn()) return;
  if (this->display->getUpdateTime() +5000 > millis()) return;
  this->config->setPosition(this->display->getPosition());
  this->config->save();
}

/**************************************************/
/****************   BUTTON    *********************/
/**************************************************/

void Stakles::button_TOP_pressed(){
  signed short int steps;
  if      (this->button_TOP.getSpeedLevel() <= 1) steps = 8;
  else if (this->button_TOP.getSpeedLevel() <= 3) steps = 16;
  else if (this->button_TOP.getSpeedLevel() <= 5) steps = this->position->milimetersToSteps(1);
  else if (this->button_TOP.getSpeedLevel() <= 9) steps = this->position->milimetersToSteps(1);
  else                                            steps = this->position->milimetersToSteps(2);
  this->encoder->write(this->display->getPosition()+steps);
  this->display->update();
}

void Stakles::button_DOWN_pressed(){
  signed short int steps;
  if      (this->button_DOWN.getSpeedLevel() <= 1) steps = 8;
  else if (this->button_DOWN.getSpeedLevel() <= 3) steps = 16;
  else if (this->button_DOWN.getSpeedLevel() <= 5) steps = this->position->milimetersToSteps(1);
  else if (this->button_DOWN.getSpeedLevel() <= 9) steps = this->position->milimetersToSteps(1);
  else                                             steps = this->position->milimetersToSteps(2);
  this->encoder->write(this->display->getPosition()-steps);
}

// Ekrane skaiciai pasikeicia su pavelavimu.
// Daznai su vienu trumpu paspaudimu pasistumia per dvi padalas.
void Stakles::button_update(){
  if (this->display->getUpdateTime() +1000 > millis()) return;
  if (this->button_TOP.isPressed()) this->button_TOP_pressed();
  if (this->button_DOWN.isPressed()) this->button_DOWN_pressed();
}


/**************************************************/
/****************   DEBUG    **********************/
/**************************************************/

void Stakles::debug_update(){
  if (this->loopCount < 100000) return;
  #ifdef IN_DEBUG_MODE
    Serial.print("\n\rB:["+String(this->button_TOP.read())+String(this->button_DOWN.read())+"]");
    Serial.print(" position:"+String(this->display->getPosition(), DEC));
    Serial.print(" height:"+String(this->display->getHeightInMilimeters(), DEC));
    Serial.print(" power:"+String(analogRead(A0), DEC));

    unsigned long interval = millis() - this->debugTime;
    Serial.print(" 100k loop in "+ String(interval, DEC) + " ms");
  #endif
  this->debugTime = millis();
  this->loopCount = 0;
}

/**************************************************/
/****************   LOOP   ************************/
/**************************************************/

void Stakles::process(){
  this->loopCount++;
  this->display->setPosition(this->encoder->read());
  if (this->display->update()) return;
  if (this->loopCount % 4 == 0) this->config_update();
  if (this->loopCount % 4 == 1) this->button_update();
  if (this->loopCount % 4 == 2) this->debug_update();
}

