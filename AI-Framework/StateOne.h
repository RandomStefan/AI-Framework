#pragma once
#include "BaseState.h"
class StateOne :
    public BaseState
{
    int counter = 0;
    void EnterState();
    BaseState* Think(int seconds);
    void ExitState();

    

};

