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
 State::Init();
 showTime = new ShowTime(hourEdit, temperature);
 hourEdit = new HourEdit(minEdit);
 minEdit = new MinEdit(showTime);
 temperature = new Temperature(hourEdit, showTime);
 State::SetRunningState(showTime);
}

void loop() { State::RunningStateLoop(); }

