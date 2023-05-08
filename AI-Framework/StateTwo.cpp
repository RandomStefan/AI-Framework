#include "StateOne.h"
#include "IdleState.h"
#include "StateTwo.h"

void StateTwo::EnterState()
{
	//cout << "Enter State 2\n";
	stateName = "State Two";
}

BaseState* StateTwo::Think(int seconds)
{
	//cout << "Thinkink in state 2" << endl;
	return new IdleState();

}

void StateTwo::ExitState()
{
	//cout << "Exit State 2\n";
	stateName = "default";
}


