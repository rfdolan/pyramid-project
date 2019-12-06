//
// Ankh.cpp
//

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"

// Game includes.
#include "Ankh.h"

Ankh::Ankh() {
  setSprite("ankh");
  setSolidness(df::SOFT);
  setAltitude(1);
  setType("Ankh");
}

int Ankh::eventHandler(const df::Event *e) {

  if (e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event = static_cast <const df::EventCollision *> (e);
    hit(p_collision_event);
    return 1;
  }

  // If we get here, we have ignored this event.
  return 0;
}

void Ankh::hit(const df::EventCollision *p_c) {
  LM.writeLog("Ankh::hit(): Collision with '%s'", 
	      p_c -> getObject1() -> getType().c_str());
}
