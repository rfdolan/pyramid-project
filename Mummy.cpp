//
// Mummy.cpp
//

// Engine includes.
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "utility.h"

// Game includes.
#include "Mummy.h"

Mummy::Mummy(Hero *p_hero) {

  // Basic Mummy attributes.
  m_move_countdown = MOVE_TIME_WANDER;
  m_think_countdown = THINK_TIME_WANDER;
  setType("Mummy");
  setAltitude(3);
  setSpeed(0);

  // Default sprite, standing.
  setSprite("mummy-white");
  stopAnimation(true);
  
  // Mummy keeps track of Hero.
  m_p_hero = p_hero;

  // Set up state machine. Starts in "wander" state.
  m_machine = StateMachine();
  m_state_wander = StateWander();
  m_state_cower = StateCower();
  m_state_chase = StateChase();
  m_state_search = StateSearch();
  m_machine.setOwner(this);
  m_machine.setState(getStateWander());
  m_machine.changeState(getStateWander());

  // Get step events.
#ifdef DF_REGISTER_INTEREST
  registerInterest(df::STEP_EVENT);
#endif
}

// Start or stop animation.
void Mummy::stopAnimation(bool stop) {
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
// Return 0 if ignored, else 1
int Mummy::eventHandler(const df::Event *e) {

  // Update state machine every step.
  if (e->getType() == df::STEP_EVENT) {
	getStateMachine()->update();
	return 1;
  }
  // If we get here, we have ignored this event.
  return 0;
}

// Return true if Hero is within sensing distance.
// Written by RFDOLAN
bool Mummy::senseHero() {
	if ((getHero()->getPosition() - getPosition()).getMagnitude() < SENSE_DISTANCE) {
		return true;
	}
	return false; // Can't sense.
}

// If can see Hero and can sense Hero, return direction
// else return (0,0).
// Written by RFDOLAN
df::Vector Mummy::seeHero() {
	// Check if in range for sensing hero.
	if (senseHero()) {
		
		// Check if line from hero to mummy has wall.
		// if not, the chase begins, return normalized vector.

		df::Vector mummy_pos = getPosition();
		df::Vector hero_pos = getHero()->getPosition();
		df::Vector v = hero_pos - mummy_pos;
		float minX = 0;
		float minY = 0;
		if (mummy_pos.getX() <= hero_pos.getX()) {
			minX = mummy_pos.getX();
		}
		else {
			minX = hero_pos.getX();
		}
		if (mummy_pos.getY() <= hero_pos.getY()) {
			minY = mummy_pos.getY();
		}
		else {
			minY = hero_pos.getY();
		}
		df::Vector corner = df::Vector(minX, minY);
		float width = abs(mummy_pos.getX() - hero_pos.getX());
		float height = abs(mummy_pos.getY() - hero_pos.getY());
		//LM.writeLog("Making box with corner (%.1f, %.1f) width: %.1f height %.1f", corner.getX(), corner.getY(), width, height);
		df::Box b = df::Box(corner, width, height);

		// Get all of the walls to check collisions with.
		df::ObjectList walls = WM.objectsOfType("Wall");
		df::ObjectListIterator i = df::ObjectListIterator(&walls);
		bool blocked = false;
		while (!i.isDone()) {
			df::Object* curr = i.currentObject();
			df::Box box = df::getWorldBox(curr);
			// If there is a wall in our way, return vector (0,0).
			if (df::boxIntersectsBox(box, b)) {
				blocked = true;
			}
			i.next();
		}
		// No intersections, we can see!
		if (!blocked) {
			v.normalize();
			return v;
		}
	}
  return df::Vector(0,0);  // Can't see.
}

void Mummy::setMoveCountdown(int new_move_countdown) {
  m_move_countdown = new_move_countdown;
}

int Mummy::getMoveCountdown() {
  return m_move_countdown;
}

void Mummy::setThinkCountdown(int new_think_countdown) {
  m_think_countdown = new_think_countdown;
}

StateCower* Mummy::getStateCower()
{
	return &m_state_cower;
}

StateChase* Mummy::getStateChase()
{
	return &m_state_chase;
}

StateSearch* Mummy::getStateSearch()
{
	return &m_state_search;
}

StateWander* Mummy::getStateWander()
{
	return &m_state_wander;
}

StateMachine* Mummy::getStateMachine()
{
	return &m_machine;
}

int Mummy::getThinkCountdown() {
  return m_think_countdown;
}

Hero *Mummy::getHero() {
  return m_p_hero;
}
