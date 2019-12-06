#pragma once
// RFDOLAN
// All code authored by Raymond Dolan for assignment
#include "State.h"
#define THINK_TIME_WANDER 90
#define MOVE_TIME_WANDER 60
class StateWander :
	public State
{
private:
	bool isThinking;
	df::Vector chooseDirection();
public:
	StateWander();

	void Enter(df::Object* p_obj);
	void Execute(df::Object* p_obj);
};

