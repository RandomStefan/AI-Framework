#pragma once
#include <SFML\Graphics.hpp>
#include "BaseEntity.h"
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

class TreeNode 
{
public:
	const double MinWidth = 8.0f;
	const double MinHeight = 8.0f;

	TreeNode(double w, double h, double xp, double yp) : width(w), height(h), x(xp), y(yp) {
		for (int i = 0; i < 4; ++i)
		{
			children[i] = nullptr;
		}
	}

	bool canFit(double objX, double objY);
	void Subdivide();
	void addObject(double oX, double oY, BaseEntity* obj);
	void Draw(sf::RenderWindow& window, sf::RectangleShape& rect);

	double width;
	double height;
	double x;
	double y;

	TreeNode* children[4];
	std::vector<BaseEntity*> objects;
};

class QuadTree
{
public:
	QuadTree(double w, double h) {
		root = new TreeNode(w, h, 0.0, 0.0);
	}

	void Draw(sf::RenderWindow& window);

	void AddObject(double x, double y, BaseEntity* obj);

	TreeNode *root;
	sf::RectangleShape shape;
};

