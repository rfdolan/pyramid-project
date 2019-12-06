#include "StateWander.h"
#include "StateMachine.h"
#include <LogManager.h>
#include "../Mummy.h"


df::Vector StateWander::chooseDirection()
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

StateWander::StateWander()
{

}

void StateWander::Enter(df::Object* p_obj)
{
	// Set wander sprite(white mummy).
	p_obj->setSprite("mummy-white");
	p_obj->setSpeed(0);
	Mummy* p_mummy = dynamic_cast<Mummy*>(p_obj);
	isThinking = true;
	p_mummy->setThinkCountdown(THINK_TIME_WANDER);
	p_mummy->setMoveCountdown(MOVE_TIME_WANDER);

	LM.writeLog("StateWander::Enter():Set mummy-white");
}

void StateWander::Execute(df::Object* p_obj)
{
	// This state deals with a Mummy
	Mummy* p_mummy = dynamic_cast<Mummy*>(p_obj);

	// Start thinking.
	if (p_mummy->getMoveCountdown() <= 0 && !isThinking) {
		LM.writeLog("Start thinking");
		// Stop moving.
		p_mummy->setSpeed(0);

		// Reset moving countdown.
		p_mummy->setMoveCountdown(MOVE_TIME_WANDER);
		isThinking = true;
	}

	// Start moving
	if (p_mummy->getThinkCountdown() <= 0 && isThinking) {
		LM.writeLog("Start walking");
		// That's enough thinking, choose a direction and start moving.
		p_mummy->setDirection(chooseDirection());
		p_mummy->setSpeed(WANDER_SPEED);

		// Reset thinking countdown.
		p_mummy->setThinkCountdown(THINK_TIME_WANDER);
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

	// If can sense Hero, enter seek state.
	if (p_mummy->senseHero()) {
		StateMachine* p_machine = p_mummy->getStateMachine();
		p_machine->changeState(p_mummy->getStateSearch());
		return;
	}
}
