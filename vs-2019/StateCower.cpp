#include "StateCower.h"
#include <LogManager.h>
#include "../Mummy.h"

StateCower::StateCower()
{

}

void StateCower::Enter(df::Object* p_obj)
{
	p_obj->setSprite("mummy-cower");

	LM.writeLog("StateCower::Enter():Set mummy-cower");
}

void StateCower::Execute(df::Object* p_obj)
{

	// This state deals with a Mummy, so case Object *.
	Mummy* p_mummy = dynamic_cast<Mummy*>(p_obj);

	// Cowering, so don't do anything.
	p_mummy->setSpeed(0);

	// See if timer is up, and if so go to appropriate state.
	if (!p_mummy->getHero()->hasAnkh()) {
		StateMachine* p_machine = p_mummy->getStateMachine();
		
		// If we can see the hero, enter chase state.
		if (!(p_mummy->seeHero()==df::Vector(0,0))) {
			p_machine->changeState(p_mummy->getStateChase());
			return;
		}
		// If can sense Hero, enter seek state.
		else if (p_mummy->senseHero()) {
			p_machine->changeState(p_mummy->getStateSearch());
			return;
		}
		// Else, we should just wander.
		else {
			p_machine->changeState(p_mummy->getStateWander());
			return;
		}
	}
}
