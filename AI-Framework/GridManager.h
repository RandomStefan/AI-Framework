#pragma once
#include "Constants.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

struct Cell
{
	Cell(int u, int v) : xPos(u), yPos(v) {}

	Cell* GetNeighbour(int dir);

	bool isMatch(int x, int y) { return x == xPos && y == yPos; }

	sf::Vector2f GetOrigin() { return sf::Vector2f{ (float)(xPos * Width) + HalfWidth, (float)(yPos * Height) + HalfHeight }; }

	const int Width = MaxCellWidth;
	const int Height = MaxCellHeight;
	const float HalfWidth = Width / 2;
	const float HalfHeight= Height / 2;

	double distance = 0.0;

	bool visited = false;

	

	int type = 0; //0 is blank space, 1 is wall, 2 is state block

	int xPos;
	int yPos;

	bool highlighted = false;
	bool endPoint = false;
	bool startPoint = false;
	bool path = false;

	std::vector<Cell*> neighbours;
	Cell* parent = nullptr;
};

class GridManager
{
public:
	GridManager();
	std::vector<Cell*> DepthSearch(Cell* start, Cell* end);
	std::vector<Cell*> BreadthSearch(Cell* start, Cell* end);
	std::vector<Cell*> Djikstras(Cell* start, Cell* end);
	std::vector<Cell*> AStar(Cell* start, Cell* end);

	int Manhattan(Cell* start, Cell* end);

	Cell* FindGridCell(int x, int y) {
		return gridCells[x][y];
	}

	int RowSize;
	int ColSize;

	void Draw(sf::RenderWindow& window, sf::Vector2i &mousePos);

	void Generate(sf::RenderWindow& window);

private:
	std::vector<std::vector<Cell*>> gridCells;
	sf::RectangleShape cellShape;
};

