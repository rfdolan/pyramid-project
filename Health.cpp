//
// Health.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "GameManager.h"		

// Game includes.
#include "game.h"
#include "Health.h"

Health::Health() {
  setViewString(HEALTH_STRING);
  setColor(df::YELLOW);
  setBorder(false);
  setLocation(df::TOP_LEFT);
  setValue(STARTING_HEALTH);
}

// Handle event.
// Return 0 if ignored, else 1.
int Health::eventHandler(const df::Event *p_e) {

  // Call parent handler.
  if (df::ViewObject::eventHandler(p_e)) {
    if (getValue() < 1)
      df::GameManager::getInstance().setGameOver();
  }
 
  // If we get here, event not handled.
  return 0;
}
