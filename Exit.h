//
// Exit.h
//

#ifndef EXIT_H
#define EXIT_H

// Engine includes.
#include "Object.h"
#include "EventCollision.h"

class Exit : public df::Object {

 protected:
  void hit(const df::EventCollision *p_c);
  int eventHandler(const df::Event *e);

 public:
  Exit();
};

#endif

