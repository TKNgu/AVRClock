#include "DayOfWeekEdit.hpp"
#include "HourEdit.hpp"
#include "MinEdit.hpp"
#include "ShowTime.hpp"
#include "State.hpp"

static State *showTime;
static State *hourEdit;
static State *minEdit;
static State *dayOfWeekEdit;

void setup() {
    State::Init(showTime = new ShowTime(
                    hourEdit = new HourEdit(
                        minEdit = new MinEdit(
                            dayOfWeekEdit = new DayOfWeekEdit(showTime)))));
}

void loop() { State::RunningStateLoop(); }

