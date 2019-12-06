#pragma once
#include <Object.h>
#include "State.h"

class StateMachine
{

private:
	df::Object* p_owner;
	State* p_state;
	State* p_previous_state;
	State* p_global_state;

public:
	StateMachine();

	// Set owner of state machine.
	void setOwner(df::Object* p_new_owner);
	// Get owner of state machine.
	df::Object* getOwner() const;
	// Set current state.
	void setState(State* p_new_state);
	// Get current state.
	State* getState() const;
	// Set previous state.
	void setPreviousState(State* p_new_state);
	// Get previous state.
	State* getPreviousState() const;
	// Set global state.
	void setGlobalState(State* p_new_state);
	// Get global state.
	State* getGlobalState() const;
	// Update state machine (calling Execute() for current state).
	void update();
	// Change current state.
	void changeState(State* p_new_state);
	// Revert to previous state.
	void revertToPrevious();
};

