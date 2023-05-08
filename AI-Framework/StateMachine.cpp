#include "StateMachine.h"


void StateMachine::Tick(int seconds)
{
	BaseState* newState = currentState->Think(seconds);
	if ((newState != nullptr) && (seconds%5==0))
	{
		currentState->ExitState();
		newState->EnterState();
		currentState = newState;


	}


}

string StateMachine::getStateName()
{
	return currentState->stateName;
}