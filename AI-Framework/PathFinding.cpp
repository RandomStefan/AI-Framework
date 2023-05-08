#include "PathFinding.h"

// the idea here is that we instantiate new boids along the path that needs to be followed and set them incrementally as destinations

void PathFinding::Think()
{
	if (destination == nullptr) return;
	sf::Vector2f movementVector; // we create a movement vector
	movementVector.x = destination->getPosition().x - getPosition().x; // we set the x and the y
	movementVector.y = destination->getPosition().y - getPosition().y; 
	float vecLength = sqrt(pow(movementVector.x, 2) + pow(movementVector.y, 2)); // we normalize it
	movementVector /= vecLength;

	if (getPosition().x != destination->getPosition().x)
		move(movementVector.x, movementVector.y); // we move it as desired
}

void PathFinding::SetPath(std::vector<Cell*> path) // here we create tha path of boids
{
	

	for each (Cell * cell in path)
	{
		Boid* pathBoid = new Boid();
		pathBoid->Initialize();
		pathBoid->skipUpdate = 1;
		pathBoid->SetTextureFile("assets\\empty.png");
		sf::Vector2f pozOfPathCell = cell->GetOrigin();
		pathBoid->setPosition(pozOfPathCell.x, pozOfPathCell.y);
		pathBoids.push_back(pathBoid); // and we get a vector of them as a result
	}

	i = pathBoids.size() - 1;
}

void PathFinding::followPath()
{
	if (i >= 0)
	{
		setDestination(pathBoids[i]); // we go through the vector and we set each boid as a destination
		i--;
	}
}
