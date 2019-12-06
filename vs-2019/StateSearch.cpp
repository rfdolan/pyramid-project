#include "StateSearch.h"
#include <LogManager.h>
#include "../Mummy.h"

df::Vector StateSearch::chooseDirection()
{
	int random = rand();
	if (random % 4 == 0) {
		return df::Vector(1, 0);
	}
	if (random % 4 == 1) {
		return df::Vector(-1, 0);
	}
	if (random % 4 == 2) {
		return df::Vector(0, 1);
	}
	if (random % 4 == 3) {
		return df::Vector(0, -1);
	}
}

StateSearch::StateSearch()
{
}

void StateSearch::Enter(df::Object* p_obj)
{
	// Set wander sprite.
	p_obj->setSprite("mummy-yellow");
	p_obj->setSpeed(SEARCH_SPEED);
	Mummy* p_mummy = dynamic_cast<Mummy*>(p_obj);
	isThinking = false;
	p_mummy->setMoveCountdown(MOVE_TIME_SEARCH);
	p_mummy->setThinkCountdown(THINK_TIME_SEARCH);
	

	LM.writeLog("StateSearch::Enter():Set mummy-yellow");
}

void StateSearch::Execute(df::Object* p_obj)
{
	// This state deals with a Mummy
	Mummy* p_mummy = dynamic_cast<Mummy*>(p_obj);

	// Move.
	// Implement searching (move faster and stop less frequently).
	// Start thinking.
	if (p_mummy->getMoveCountdown() <= 0 && !isThinking) {
		LM.writeLog("Start thinking");
		// Stop moving.
		p_mummy->setSpeed(0);

		// Reset moving countdown.
		p_mummy->setMoveCountdown(MOVE_TIME_SEARCH);
		isThinking = true;
	}

	// Start moving
	if (p_mummy->getThinkCountdown() <= 0 && isThinking) {
		LM.writeLog("Start walking");
		// That's enough thinking, choose a direction and start moving.
		p_mummy->setDirection(chooseDirection());
		p_mummy->setSpeed(SEARCH_SPEED);

		// Reset thinking countdown.
		p_mummy->setThinkCountdown(THINK_TIME_SEARCH);
		isThinking = false;
	}
	// Decrement appropriate counter.
	if (isThinking) {
		p_mummy->setThinkCountdown(p_mummy->getThinkCountdown() - 1);
	}
	else {
		p_mummy->setMoveCountdown(p_mummy->getMoveCountdown() - 1);
	}

	// If Hero has ankh, enter cower state.
	if (p_mummy->getHero()->hasAnkh()) {
		StateMachine* p_machine = p_mummy->getStateMachine();
		p_machine->changeState(p_mummy->getStateCower());
		return;
	}


	
	// If we can see the hero, go into chase mode.
	if (!(p_mummy->seeHero() == df::Vector(0,0))) {
		StateMachine* p_machine = p_mummy->getStateMachine();
		p_machine->changeState(p_mummy->getStateChase());
		return;
	}
	// If we cannot sense the hero, go into wander mode
	if (!p_mummy->senseHero()) {
		StateMachine *p_machine = p_mummy->getStateMachine();
		p_machine->changeState(p_mummy->getStateWander());
		return;
	}

}
