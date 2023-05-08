#pragma once
#include <SFML/Graphics.hpp>

inline float Distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	sf::Vector2f c = a - b;

	return std::sqrtf(c.x * c.x + c.y * c.y);
}

inline float Magnitude(const sf::Vector2f& a)
{
	return std::sqrtf(a.x * a.x + a.y * a.y);
}