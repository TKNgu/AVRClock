#include "HourEdit.hpp"
#include "MinEdit.hpp"
#include "ShowTime.hpp"
#include "State.hpp"
#include "Temperature.hpp"

static State *showTime;
static State *hourEdit;
static State *minEdit;
static State *temperature;

void setup() {
 showTime = new ShowTime(hourEdit);
 hourEdit = new HourEdit(minEdit);
 minEdit = new MinEdit(showTime);
 temperature = new Temperature(showTime);

 State::SetRunningState(temperature);
}

void loop() {
 State::RunningStateLoop();
}

