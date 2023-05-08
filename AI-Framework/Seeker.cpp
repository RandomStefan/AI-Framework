#include "Seeker.h"
#include "UtilFunc.h"

void Seeker::Think()
{

	if (target == nullptr) return;
	sf::Vector2f moveVec;
	moveVec.x = getPosition().x - target->getPosition().x;
	moveVec.y = getPosition().y - target->getPosition().y;
	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));
	moveVec /= vecLength;

	if (getPosition().x != target->getPosition().x)
		move(moveVec.x, moveVec.y);

	applyForce(moveVec);
}

