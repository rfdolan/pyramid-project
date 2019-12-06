#include "State.h"
#include "State.h"

State::State()
{
}

void State::setType(std::string new_type)
{
	state_type = new_type;
}

std::string State::getType() const
{
	return state_type;
}

void State::Enter(df::Object* p_obj)
{
}

void State::Exit(df::Object* p_obj)
{
}
