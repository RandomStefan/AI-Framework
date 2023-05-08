#include "IdleState.h"
#include "StateOne.h"
#include "StateTwo.h"


BaseState* IdleState::Think(int seconds)
{
	//cout << "IdleThink\n";

	if (seconds % 5==0 && seconds >0)
		return new StateOne();
	else if (seconds%2 == 0)
		return new StateTwo();

}

void IdleState::ExitState()
{
	//cout << "Exit Idle State\n";
	stateName = "default";
}

void IdleState::EnterState()
{
	//cout << "Enter Idle State\n";
	stateName = "Idle";

}
