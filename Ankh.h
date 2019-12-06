//
// Ankh.h
//

#ifndef ANKH_H
#define ANKH_H

// Engine includes.
#include "EventCollision.h"
#include "Object.h"

class Ankh : public df::Object {

 protected:
  void hit(const df::EventCollision *p_c);
  int eventHandler(const df::Event *e);

 public:
  Ankh();
};

#endif

