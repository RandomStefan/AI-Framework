#include "QuadTree.h"

void QuadTree::Draw(sf::RenderWindow& window)
{
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.0f);
	root->Draw(window, shape);
}

void QuadTree::AddObject(double x, double y, BaseEntity* obj)
{
	root->addObject(x, y, obj);
}

void TreeNode::addObject(double oX, double oY, BaseEntity* obj)
{
	if (children[0] == nullptr && canFit(oX, oY)) {
		if (width > MinWidth && height > MinHeight)
			Subdivide();
		else
		{
			objects.push_back(obj);
			return;
		}
	}

	for (TreeNode* child : children)
	{
		if (child == nullptr) continue;
		child->addObject(oX, oY, obj);
	}
}

void TreeNode::Draw(sf::RenderWindow& window, sf::RectangleShape& rect)
{
	for (TreeNode* child : children)
	{
		if ( child != nullptr)
			child->Draw(window, rect);
	}

	//rect.setOrigin(x - width / 2, y - height / 2);
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	window.draw(rect);
}

bool TreeNode::canFit(double objX, double objY)
{
	return  objX >= x &&
		objX < x + width &&
		objY >= y &&
		objY < y + height;
}

void TreeNode::Subdivide()
{
	if (children[0] != nullptr) return;

	double halfWidth = width / 2;
	double halfHeight = height / 2;

	children[0] = new TreeNode(halfWidth, halfHeight, x, y);
	children[1] = new TreeNode(halfWidth, halfHeight, x + halfWidth, y);
	children[2] = new TreeNode(halfWidth, halfHeight, x + halfWidth, y + halfHeight);
	children[3] = new TreeNode(halfWidth, halfHeight, x, y + halfHeight);
}


