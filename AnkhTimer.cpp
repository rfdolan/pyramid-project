//
// AnkhTimer.cpp
//

// Engine includes.
#include "EventStep.h"
#include "WorldManager.h"

// Game includes.
#include "AnkhTimer.h"

AnkhTimer::AnkhTimer() {
  setLocation(df::TOP_CENTER);
  setViewString(ANKH_TIMER_STRING);
  setColor(df::CYAN);
  setBorder(false);

  // Need to update time each second, so count "step" events.
#ifdef DF_REGISTER_INTEREST
  registerInterest(df::STEP_EVENT);
#endif
  step_count = 0;
}

// Handle event.
// Return 0 if ignored, else 1.
int AnkhTimer::eventHandler(const df::Event *p_e) {

  // If step, increment score every second (30 steps)
  if (p_e->getType() == df::STEP_EVENT) {
    step_count++;
    if (step_count == 30) {	// 1 second has elapsed
      setValue(getValue() - 1);
      step_count = 0;
      if (getValue() == 0)
	WM.markForDelete(this);
    }
    return 1;
  }

  // if we get here, we have ignored this event
  return 0;
}
