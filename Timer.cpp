//
// Timer.cpp
//

// Engine includes.
#include "DisplayManager.h"	
#include "EventStep.h"
#include "LogManager.h"

// Game includes.
#include "Timer.h"

Timer::Timer() {
  setViewString(TIMER_STRING);
  setColor(df::YELLOW);
  setBorder(false);
  setLocation(df::TOP_RIGHT);
  setValue(0);

  // Need to update time each second, so count "step" events.
#ifdef DF_REGISTER_INTEREST
  registerInterest(df::STEP_EVENT);
#endif
  step_count = 0;
}

// Handle event.
int Timer::eventHandler(const df::Event *p_e) {

  // If step, increment score every second (30 steps)
  if (p_e->getType() == df::STEP_EVENT) {
    step_count++;
    if (step_count == 30) {	// 1 second has elapsed
      setValue(getValue() + 1);
      step_count = 0;
    }
    return 1;
  }

  // If we get here, have ignored this event.
  return 0;
}
