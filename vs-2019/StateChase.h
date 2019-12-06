#pragma once
// RFDOLAN
// All code authored by Raymond Dolan for assignment
#include "State.h"
class StateChase :
	public State
{
public:
	StateChase();

	void Enter(df::Object* p_obj);
	void Execute(df::Object* p_obj);
};

