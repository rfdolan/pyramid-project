//
// AnkhTimer.h
// 

// Engine includes.
#include "Event.h"		
#include "ViewObject.h"

#define ANKH_TIMER_STRING "Time"

class AnkhTimer : public df::ViewObject {

 private:
  int step_count;

 public:
  AnkhTimer();
  int eventHandler(const df::Event *p_e);
};

