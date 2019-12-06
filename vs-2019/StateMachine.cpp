#include "StateMachine.h"
#include "StateMachine.h"

StateMachine::StateMachine()
{
	p_state = NULL;
	p_owner = NULL;
	p_previous_state = NULL;
	p_global_state = NULL;


}

void StateMachine::setOwner(df::Object* p_new_owner)
{
	p_owner = p_new_owner;
}

df::Object* StateMachine::getOwner() const
{
	return p_owner;
}

void StateMachine::setState(State* p_new_state)
{
	p_state = p_new_state;
}

State* StateMachine::getState() const
{
	return p_state;
}

void StateMachine::setPreviousState(State* p_new_state)
{
	p_previous_state = p_new_state;
}

State* StateMachine::getPreviousState() const
{
	return p_previous_state;
}

void StateMachine::setGlobalState(State* p_new_state)
{
	p_global_state = p_new_state;
}

State* StateMachine::getGlobalState() const
{
	return p_global_state;
}

void StateMachine::update()
{
	// Execute global state.
	if (p_global_state != NULL) {
		p_global_state->Execute(p_owner);
	}

	// Execute local state.
	if (p_state != NULL) {
		p_state->Execute(p_owner);
	}

}

void StateMachine::changeState(State* p_new_state)
{
	// Call exit on old state.
	if (p_state != NULL) {
		p_state->Exit(p_owner);
	}

	// Keep track of previous state.
	p_previous_state = p_state;

	// Change to new state.
	p_state = p_new_state;

	// Call enter on new state.
	if (p_state != NULL) {
		p_state->Enter(p_owner);
	}
}

void StateMachine::revertToPrevious()
{
	changeState(p_previous_state);
}
