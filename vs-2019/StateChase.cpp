#include "StateChase.h"
#include <LogManager.h>
#include "../Mummy.h"

StateChase::StateChase()
{

}

void StateChase::Enter(df::Object* p_obj)
{
	// Set chase sprite.
	p_obj->setSprite("mummy-red");
	p_obj->setSpeed(CHASE_SPEED);

	LM.writeLog("StateChase::Enter():Set mummy-red");
}

void StateChase::Execute(df::Object* p_obj)
{
	
	// This state deals with a Mummy, so case Object *.
	Mummy* p_mummy = dynamic_cast<Mummy*>(p_obj);

	// Move
	// Implement chasing.
	p_mummy->setDirection(p_mummy->seeHero());

	// If Hero has ankh, enter cower state.
	if (p_mummy->getHero()->hasAnkh()) {
		StateMachine* p_machine = p_mummy->getStateMachine();
		p_machine->changeState(p_mummy->getStateCower());
		return;
	}

	// If cannot see hero, enter seek.
	if (p_mummy->seeHero() == df::Vector(0,0)) {
		StateMachine *p_machine = p_mummy->getStateMachine();
		p_machine->changeState(p_mummy->getStateSearch());
	}
}
