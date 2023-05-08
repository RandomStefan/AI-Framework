#include "StateOne.h"
#include "IdleState.h"
#include "StateTwo.h"


void StateOne::EnterState()
{
	//cout << "Enter State 1\n";
	stateName = "State One";
}

BaseState* StateOne::Think(int seconds)
{
	//cout << "Thinking on state 1" << endl;
	return new IdleState();

}

void StateOne::ExitState()
{
	//cout << "Exit State 2\n";
	stateName = "default";
}
