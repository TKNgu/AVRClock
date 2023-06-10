#include "ShowTime.hpp"
#include <Arduino.h>

ShowTime::ShowTime(EditHour *&editHour) : SleepState(250), editHour(editHour)
{
  pointOn = 2;
  pointOff = 4;
  stateKey = false;
  pinMode(11, INPUT_PULLUP);
}

void ShowTime::update(State *&state)
{
  Serial.println("Update show time");
  if (!stateKey && digitalRead(11) == LOW)
  {
    stateKey = true;
    if (isLowFrequency)
    {
      Serial.println("Up");
      upFrequency();
    }
  }
  else if (stateKey && digitalRead(11) == HIGH)
  {
    stateKey = false;
    state = this->editHour;
  }
  display.time(time.getHour(), time.getMin());
  if (countTime == pointOn)
  {
    display.pointOn();
  }
  else if (countTime == pointOff)
  {
    countTime = 0;
    display.pointOff();
    if (!stateKey && !isLowFrequency && !--delayDownFrequency)
    {
      Serial.println("Down");
      downFrequency();
    }
  }
  countTime++;
}

void ShowTime::upFrequency()
{
  pointOn = 50;
  pointOff = 100;
  countTime = countTime * 25;
  delayDownFrequency = 3;
  isLowFrequency = false;
  setDelayTime(10);
}

void ShowTime::downFrequency()
{
  pointOn = 2;
  pointOff = 4;
  countTime = countTime / 25;
  isLowFrequency = true;
  setDelayTime(250);
}