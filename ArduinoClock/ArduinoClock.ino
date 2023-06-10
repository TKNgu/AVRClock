#include "HourEdit.hpp"
#include "MinEdit.hpp"
#include "ShowTime.hpp"
#include "State.hpp"

static State *showTime;
static State *hourEdit;
static State *minEdit;

void setup() {
 showTime = new ShowTime(hourEdit);
 hourEdit = new HourEdit(minEdit);
 minEdit = new MinEdit(showTime);

 State::SetRunningState(showTime);
}

void loop() {
 State::RunningStateLoop();
}

