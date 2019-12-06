//
// Hero.cpp
//

// Engine includes.
#include "EventOut.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "utility.h"

// Game includes.
#include "Ankh.h"
#include "AnkhTimer.h"
#include "Hero.h"

Hero::Hero() {

  // Hero attributes.
  setType("Hero");
  setSprite("walk");
  stopAnimation(true);
  setSpeed(0);
  setAltitude(4);
  m_ankh_countdown = 0;
  
#ifdef DF_REGISTER_INTEREST
  // Need to control Hero with keyboard.
  registerInterest(df::KEYBOARD_EVENT);

  // Need to update move countdown each step.
  registerInterest(df::STEP_EVENT);
#endif 
}

// Start or stop animation.
void Hero::stopAnimation(bool stop) {
  df::Animation animation = getAnimation();
  if (stop) {
    if (animation.getSlowdownCount() != -1) {
      animation.setSlowdownCount(-1);
      animation.setIndex(0);
    }
  } else {
    if (animation.getSlowdownCount() == -1) {
      animation.setSlowdownCount(0);
      animation.setIndex(0);
    }
  }
  setAnimation(animation);
}  

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(const df::Event *e) {

  if (e->getType() == df::KEYBOARD_EVENT) {
    const df::EventKeyboard *p_keyboard_event=(const df::EventKeyboard *) (e);
    kbd(p_keyboard_event);
    return 1;
  }

  if (e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  if (e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event=(const df::EventCollision *) (e);
    hit(p_collision_event);
    return 1;
  }

  // If we get here, have ignored this event.
  return 0;
}

// Method to handle collisions.
void Hero::hit(const df::EventCollision *p_c) {

  // If hit Mummy, take damage.
  if (p_c->getObject1()->getType() == "Mummy" ||
      p_c->getObject2()->getType() == "Mummy")  {
    // Send "view" event to Heath HUD indicating damage.
    df::EventView ev("Health", -1, true);
    WM.onEvent(&ev);
  }

  // If hit Ankh, remove and start Ankh timer.
  if (p_c->getObject2()->getType() == "Ankh")  {
    WM.markForDelete(p_c->getObject2());
    m_ankh_countdown = ANKH_TIME * 30;
    AnkhTimer *p_timer = new AnkhTimer;
    p_timer -> setValue(ANKH_TIME);
  }
}

void Hero::step() {

  // Decrement ankh count.
  m_ankh_countdown--;
  if (m_ankh_countdown < 0)
    m_ankh_countdown = -1;
}

bool Hero::hasAnkh() {
  if (m_ankh_countdown > 0)
    return true;
  else
    return false;
}

// Handle
void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {

  if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
    stopAnimation(true);
  
  switch(p_keyboard_event->getKey()) {
  case df::Keyboard::Q:		 // Q to quit.
    GM.setGameOver();
    break;
  case df::Keyboard::UPARROW:	 // up arrow
  case df::Keyboard::DOWNARROW:	 // down arrow
  case df::Keyboard::LEFTARROW:	 // left arrow
  case df::Keyboard::RIGHTARROW: // right arrow
    move(p_keyboard_event);
    break;
  default:
    break;
  };

  return;
}

// Move according to the key held down.
void Hero::move(const df::EventKeyboard *p_keyboard_event) {

  switch(p_keyboard_event->getKey()) {
  case df::Keyboard::UPARROW:
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
      df::Vector v(getVelocity().getX(), -HERO_SPEED.getY());
      setVelocity(v);
    } else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)  {
      df::Vector v(getVelocity().getX(), 0);
      setVelocity(v);
    }
    break;
  case df::Keyboard::DOWNARROW:
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
      df::Vector v(getVelocity().getX(), HERO_SPEED.getY());
      setVelocity(v);
    } else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
      df::Vector v(getVelocity().getX(), 0);
      setVelocity(v);
    }
    break;
  case df::Keyboard::LEFTARROW:		
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
      df::Vector v(-HERO_SPEED.getX(), getVelocity().getY());
      setVelocity(v);
    } else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
      df::Vector v(0, getVelocity().getY());
      setVelocity(v);
    }
    break;
  case df::Keyboard::RIGHTARROW:
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
      df::Vector v(HERO_SPEED.getX(), getVelocity().getY());
      setVelocity(v);
    } else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
      df::Vector v(0, getVelocity().getY());
      setVelocity(v);
    }
    break;
  default:
    break;
  };

  // If not moving, stop animation.
  if (getSpeed() == 0)
    stopAnimation(true);
  else
    stopAnimation(false);

  return;
}
