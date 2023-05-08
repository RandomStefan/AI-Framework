#pragma once
#include "BaseEntity.h"
class Seeker :
    public BaseEntity
{
public:
    void Think();
    void SetTarget(BaseEntity* newTarget) { target = newTarget; }

private:
    BaseEntity* target;
};
