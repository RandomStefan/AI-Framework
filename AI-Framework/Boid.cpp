#include "Boid.h"
#include "UtilFunc.h"

void Boid::Think()
{
	FindCurrentNeighbours();

	// accumulate the results from the 3 boids rules
	sf::Vector2f force;
	// separation
	force += Separation() * SeparationWeighting;
	// cohesion
	force += Cohesion() * CohesionWeighting;
	// alignment
	force += Alignment() * AlignmentWeighting;

	applyForce(force);
}

sf::Vector2f Boid::Separation()
{
	sf::Vector2f separation;
	int closeNeighbours = 0;
	// go through all boids in the neighbourhood
	for (int i = 0; i < neighbours.size(); ++i) {
		// subtract position of boid to neighbour
		sf::Vector2f diff = getPosition() - neighbours[i]->getPosition();
		float mag = Magnitude(diff);

		if (mag < DesiredMinimalDistance && mag > 0)
		{
			separation += diff / mag;
			closeNeighbours++;
		}
	}

	// it's an average, so we need to divide the force by the number of neighbours.
	if (closeNeighbours > 0)
		separation /= (float)closeNeighbours;

	return separation;
}

sf::Vector2f Boid::Alignment()
{
	sf::Vector2f alignment;
	// iterate all neighbouring boids
	for (int i = 0; i < neighbours.size(); ++i) {
		// sum their velocity
		alignment += neighbours[i]->getVelocity();
	}
	// average it
	if (neighbours.size() > 0)
	{
		alignment /= (float)neighbours.size();

		//alignment = velocity - alignment;
	}

	float mag = Magnitude(alignment);
	if (mag == 0.0f)
		mag = 1.0f;

	return alignment / mag;
}

sf::Vector2f Boid::Cohesion()
{
	sf::Vector2f cohesion;

	if (neighbours.size() > 0)
	{

		sf::Vector2f centerOfMass;

		for (auto const& flockmate : neighbours)
		{
			centerOfMass += flockmate->getPosition();
		}

		centerOfMass /= static_cast<float>(neighbours.size());

		//Get direction toward center of mass
		sf::Vector2f towardCenter = centerOfMass - getPosition();

		cohesion = towardCenter / Magnitude(towardCenter);
	}

	return cohesion;
}

void Boid::FindCurrentNeighbours()
{
	// reset the neighbourhood every frame
	neighbours.clear();

	// iterate the renderables vector
	for (int i = 0; i < BaseEntity::Renderables.size(); ++i) {
		BaseEntity* current = BaseEntity::Renderables[i];

		// check we're not looking at ourselves.
		if (current == this) continue;

		// calculate the distance between the the neighbour and the boid
		float distance = Distance(getPosition(), current->getPosition());

		// is the current boid we're looking at inside our neighbourhood?
		if (distance > NeighbourhoodSize) continue;

		// all good? add it to the neighbourhood
		neighbours.push_back(current);
	}
}
