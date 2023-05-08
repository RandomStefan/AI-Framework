#pragma once
#include "BaseEntity.h"
#include "GridManager.h"
#include "Boid.h"
#include "StateMachine.h"
#include "vector"
class PathFinding :
    public BaseEntity
{
public:
    
    void Think();
    std::vector<Boid*> pathBoids;
    int i;
    void SetPath(std::vector<Cell*> cells);
    void followPath();
    void setDestination(BaseEntity* newDest) { destination = newDest; }
    
private:
    BaseEntity* destination;
   
};

