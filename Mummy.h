//
// Mummy.h
//

#ifndef MUMMY_H
#define MUMMY_H

// Engine includes
#include "Event.h"
#include "Object.h"
#include "Vector.h"

// Game includes
#include "game.h"
#include "Hero.h"
#include "vs-2019\StateMachine.h"
#include "vs-2019\StateCower.h"
#include "vs-2019\StateChase.h"
#include "vs-2019\StateSearch.h"
#include "vs-2019\StateWander.h"
#define SENSE_DISTANCE 30
#define CHASE_SPEED 0.35
#define WANDER_SPEED 0.05
#define SEARCH_SPEED 0.15

class Mummy : public df::Object {

 private:
  Hero *m_p_hero;
  int m_move_countdown;
  int m_think_countdown;
  StateMachine m_machine;
  StateCower m_state_cower;
  StateChase m_state_chase;
  StateSearch m_state_search;
  StateWander m_state_wander;

 public:
  Mummy(Hero *p_hero);
  int eventHandler(const df::Event *e);
  Hero *getHero();
  void stopAnimation(bool stop);
  df::Vector seeHero(); // Written by RFDOLAN
  bool senseHero(); // Written by RFDOLAN
  int getMoveCountdown();
  void setMoveCountdown(int new_move_countdown);
  int getThinkCountdown();
  void setThinkCountdown(int new_think_countdown);


  StateCower* getStateCower();
  StateChase* getStateChase();
  StateSearch* getStateSearch();
  StateWander* getStateWander();
  StateMachine* getStateMachine();

};

#endif
