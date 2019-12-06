//
// Timer.h
// 

// Engine includes.
#include "Event.h"		
#include "ViewObject.h"

#define TIMER_STRING "Time"

class Timer : public df::ViewObject {

 private:
  int step_count;

 public:
  Timer();
  int eventHandler(const df::Event *p_e);
};

