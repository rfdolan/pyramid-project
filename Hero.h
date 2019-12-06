//
// Hero.h
//

#ifndef HERO_H
#define HERO_H

// Engine includes.
#include "Object.h"
#include "EventKeyboard.h"
#include "EventCollision.h"

// Game includes.
#include "game.h"

class Hero : public df::Object {
 private:
  void step();
  void kbd(const df::EventKeyboard *keyboard_event);
  void move(const df::EventKeyboard *p_keyboard_event);
  void hit(const df::EventCollision *p_c);
  int m_ankh_countdown;

 public:
  Hero();
  void stopAnimation(bool stop);
  int eventHandler(const df::Event *e);
  bool hasAnkh();
};
#endif
