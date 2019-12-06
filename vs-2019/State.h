#pragma once
#include <string>
#include <Object.h> 

class State
{
private:
	std::string state_type;

public:
	State();

	// Set name of state.
	void setType(std::string new_type);

	// Get name of state.
	std::string getType() const;

	// Invoked when stae first entered.
	virtual void Enter(df::Object* p_obj);

	// Invoked every game loop step.
	virtual void Execute(df::Object* p_obj) = 0;

	// Invoked when state exited.
	virtual void Exit(df::Object* p_obj);
};

