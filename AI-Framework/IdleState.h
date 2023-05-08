#pragma once
#include "BaseState.h"
class IdleState :
    public BaseState
{
    void EnterState();
    BaseState* Think(int seconds);
    void ExitState();

};

