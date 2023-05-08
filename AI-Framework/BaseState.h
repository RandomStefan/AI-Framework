#pragma once
#include "BaseEntity.h"
#include "string"
#include <iostream>
using namespace std;

class BaseState
{
	
public:
	
	virtual void EnterState() = 0;
	virtual BaseState* Think(int seconds) = 0;
	virtual void ExitState() = 0;
	string stateName = "default";

};