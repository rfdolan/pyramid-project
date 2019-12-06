//
// Exit.cpp
//

#include "Exit.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "GameManager.h"

Exit::Exit() {
  LM.writeLog("Exit::Exit(): Just added to game world");
  if (setSprite("exit") == -1)
    LM.writeLog("Exit::Exit(): Warning! Sprite '%s' not found", "exit");
  setSolidness(df::SOFT);
  setType("Exit");
  setAltitude(2);
}

int Exit::eventHandler(const df::Event *e) {

  if (e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event = static_cast <const df::EventCollision *> (e);
    hit(p_collision_event);
    return 1;
  }

  // if we get here, we have ignored this event
  return 0;
}

void Exit::hit(const df::EventCollision *p_c) {
  LM.writeLog("Exit::hit(): Collision with '%s'", 
	      p_c -> getObject1() -> getType().c_str());

  if (p_c -> getObject1() -> getType() == "Hero")
    GM.setGameOver();
}
