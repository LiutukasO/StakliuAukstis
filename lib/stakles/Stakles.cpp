#include <Stakles.h>


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
  this->button_TOP = Button(buttonTopPin);
  this->button_DOWN = Button(buttonDownPin);
  this->config = new Config();
  this->encoder = new Encoder(encoderPinA, encoderPinB);
  this->encoder->write(this->position->fitPositionToValidRange(this->config->getPosition()));
}

/**************************************************/
/****************   CONFIG    *********************/
/**************************************************/

bool Stakles::config_update(){
  if (!this->config->setPosition(this->display->getPosition())) return false;
  if (this->powerDetector->isPowerOn()) return false;
  return this->config->save();
}

/**************************************************/
/****************   BUTTON    *********************/
/**************************************************/

void Stakles::button_TOP_pressed(){
  signed short int steps = 1;
  if      (this->button_TOP.getSpeedLevel() <= 1) steps = 1;
  else if (this->button_TOP.getSpeedLevel() <= 3) steps = this->position->milimetersToSteps(1);
  else if (this->button_TOP.getSpeedLevel() <= 5) steps = this->position->milimetersToSteps(2);
  else if (this->button_TOP.getSpeedLevel() <= 9) steps = this->position->milimetersToSteps(3);
  else                                            steps = this->position->milimetersToSteps(5);
  this->encoder->write(this->display->getPosition()+steps);
}

void Stakles::button_DOWN_pressed(){
  signed short int steps = 1;
  if      (this->button_DOWN.getSpeedLevel() <= 1) steps = 1;
  else if (this->button_DOWN.getSpeedLevel() <= 3) steps = this->position->milimetersToSteps(1);
  else if (this->button_DOWN.getSpeedLevel() <= 5) steps = this->position->milimetersToSteps(2);
  else if (this->button_DOWN.getSpeedLevel() <= 9) steps = this->position->milimetersToSteps(3);
  else                                             steps = this->position->milimetersToSteps(5);
  this->encoder->write(this->display->getPosition()-steps);
}

void Stakles::button_update(){
  if (this->button_TOP.isPressed()) this->button_TOP_pressed();
  if (this->button_DOWN.isPressed()) this->button_DOWN_pressed();
}


/**************************************************/
/****************   ENCODER    ********************/
/**************************************************/


bool Stakles::encoder_update(){
  return this->display->setPosition(this->encoder->read());
}


/**************************************************/
/****************   DEBUG    **********************/
/**************************************************/

bool Stakles::debug_update(){
  if (this->loopCount < 100000) return false;
  Serial.print("\n\rB:["+String(this->button_TOP.read())+String(this->button_DOWN.read())+"]");
  Serial.print(" position:"+String(this->display->getPosition(), DEC));
  Serial.print(" height:"+String(this->display->getHeightInMilimeters(), DEC));
  Serial.print(" power:"+String(analogRead(A0), DEC));

  unsigned long interval = millis() - this->debugTime;
  Serial.print(" 100k loop in "+ String(interval, DEC) + " ms");

  this->debugTime = millis();
  this->loopCount = 0;
  return true;
}

/**************************************************/
/****************   LOOP   ************************/
/**************************************************/

void Stakles::process(){
  this->loopCount++;
  if (this->display->update()) return;
  if (this->encoder_update()) return;
  if (this->loopCount % 4 == 0) {
    this->config_update();
    this->button_update();
    this->debug_update();
  }
}

