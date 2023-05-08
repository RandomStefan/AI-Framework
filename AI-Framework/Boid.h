#pragma once
#include "BaseEntity.h"
class Boid :
    public BaseEntity
{
public:
    void Think();

    // radius to check for neighbours around each boid
    const float NeighbourhoodSize = 300.0f;

    const float SeparationWeighting = 2.5f;
    const float DesiredMinimalDistance = 150.0f;

    const float AlignmentWeighting = 1.0f;
    const float CohesionWeighting = 1.0f;

private:
    sf::Vector2f Separation();
    sf::Vector2f Alignment();
    sf::Vector2f Cohesion();

    void FindCurrentNeighbours();

    std::vector<BaseEntity*> neighbours;
};

