#include "EditHour.hpp"
#include <Arduino.h>

EditHour::EditHour() : SleepState(250)
{
  countTime = 0;
  pointOn = 2;
  pointOff = 4;
  stateKey = false;
  pinMode(11, INPUT_PULLUP);
}

void EditHour::update(State *&state)
{
  if (!stateKey && digitalRead(11) == LOW)
  {
    stateKey = true;
  }
  else if (stateKey && digitalRead(11) == HIGH)
  {
    stateKey = false;
  }
  display.time(time.getHour(), time.getMin());
  if (countTime == pointOn)
  {
    Serial.println("ON");
    display.pointOn();
  }
  else if (countTime == pointOff)
  {
    Serial.println("OFF");
    countTime = 0;
    display.pointOff();
  }
  countTime++;
}