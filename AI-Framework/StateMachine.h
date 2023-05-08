#pragma once
#include "BaseState.h"
#include "IdleState.h"
class StateMachine 
{
public:
	BaseState* currentState;
	StateMachine()
	{
		currentState = new IdleState();
	}
	string getStateName();
	void Tick(int seconds);
};

