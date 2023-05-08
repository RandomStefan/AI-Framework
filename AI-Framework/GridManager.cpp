#include "GridManager.h"

#include <stack>
#include <queue>
#include <iostream>

GridManager::GridManager()
{
	int rowWidth = (ScreenWidth / MaxCellWidth);
	int rowHeight = (ScreenHeight / MaxCellHeight);
	
	RowSize = rowWidth;
	ColSize = rowHeight;

	for (int i = 0; i < rowHeight; ++i)
	{
		gridCells.push_back(std::vector<Cell*>());
		for (int j = 0; j < rowWidth; ++j) {
			gridCells[i].push_back(new Cell(j, i));
		}
	}

	for (int i = 0; i < rowHeight; ++i)
	{
		for (int j = 0; j < rowWidth; ++j) {

			if (i > 0) // top neighbour
				gridCells[i][j]->neighbours.push_back(gridCells[i - 1][j]);
			else
				gridCells[i][j]->neighbours.push_back(nullptr);

			if (i + 1 <= rowHeight - 1) // bottom neighbour
				gridCells[i][j]->neighbours.push_back(gridCells[i + 1][j]);
			else
				gridCells[i][j]->neighbours.push_back(nullptr);

			if (j > 0) // left neighbour
				gridCells[i][j]->neighbours.push_back(gridCells[i][j - 1]);
			else
				gridCells[i][j]->neighbours.push_back(nullptr);

			if (j + 1 <= rowWidth - 1) // right neighbour
				gridCells[i][j]->neighbours.push_back(gridCells[i][j + 1]);
			else
				gridCells[i][j]->neighbours.push_back(nullptr);
		}
	}

	cellShape.setOutlineColor(sf::Color::Green);
	cellShape.setOutlineThickness(1.0f);
	cellShape.setFillColor(sf::Color::Transparent);
	cellShape.setSize(sf::Vector2f(MaxCellWidth, MaxCellHeight));
}

std::vector<Cell*> GridManager::DepthSearch(Cell* start, Cell* end)
{
	std::stack<Cell*> searchStack;

	start->startPoint = true;
	end->endPoint = true;
	bool found = false;
	searchStack.push(start);
	start->visited = true;
	while (!searchStack.empty())
	{
		Cell* currentNode = searchStack.top();
		searchStack.pop();
		
		if (currentNode == end)
		{
			found = true;
			break;
		}

		if (currentNode->neighbours.size() == 0) break;
	
		while (currentNode->GetNeighbour(2) != nullptr)
		{
			Cell* neighbour = currentNode->GetNeighbour(2);
			if (neighbour != nullptr)
			{
				if (!neighbour->visited)
				{
					neighbour->parent = currentNode;
					searchStack.push(neighbour);
					neighbour->visited = true;
				}

				currentNode = neighbour;
			}
		}

		while (currentNode->GetNeighbour(1) != nullptr)
		{
			Cell* neighbour = currentNode->GetNeighbour(1);
			if (neighbour != nullptr)
			{
				if (!neighbour->visited)
				{
					neighbour->parent = currentNode;
					searchStack.push(neighbour);
					neighbour->visited = true;
				}

				currentNode = neighbour;
			}
		}

		while (currentNode->GetNeighbour(3) != nullptr)
		{
			Cell* neighbour = currentNode->GetNeighbour(3);
			if (neighbour != nullptr)
			{
				if (!neighbour->visited)
				{
					neighbour->parent = currentNode;
					searchStack.push(neighbour);
					neighbour->visited = true;
				}

				currentNode = neighbour;
			}
		}

		while (currentNode->GetNeighbour(0) != nullptr)
		{
			Cell* neighbour = currentNode->GetNeighbour(0);
			if (neighbour != nullptr)
			{
				if (!neighbour->visited)
				{
					neighbour->parent = currentNode;
					searchStack.push(neighbour);
					neighbour->visited = true;
				}

				currentNode = neighbour;
			}
		}
	}

	std::vector<Cell*> path;
	if (!found) return path;

	path.push_back(end);

	Cell* pathNode = end->parent;
	while (pathNode != nullptr)
	{
		path.push_back(pathNode);
		pathNode->path = true;
		pathNode = pathNode->parent;
	}

	std::reverse(path.begin(), path.end());

	return path;
}

std::vector<Cell*> GridManager::BreadthSearch(Cell* start, Cell* end)
{
	for (std::vector<Cell*> row : gridCells)
	{
		for (Cell* cell : row)
		{
			cell->distance = DBL_MAX;
			cell->parent = nullptr;
		}
	}

	std::queue<Cell*> searchQueue;

	start->startPoint = true;
	end->endPoint = true;
	start->distance = 0.0f;

	searchQueue.push(start);
	bool found = false;
	while (!searchQueue.empty())
	{
		Cell* current = searchQueue.front();
		searchQueue.pop();

		for (Cell* neighbour : current->neighbours)
		{
			if (neighbour == nullptr) continue;
			if (neighbour->distance == DBL_MAX)
			{
				neighbour->parent = current;
				neighbour->visited = true;
				neighbour->distance = current->distance + 1.0;
				if (neighbour == end)
				{
					found = true;
					break;
				}
				searchQueue.push(neighbour);
			}
		}

		if (found) break;
	}

	std::vector<Cell*> path;
	if (!found) return path;

	path.push_back(end);

	Cell* pathNode = end->parent;
	while (pathNode != nullptr)
	{
		path.push_back(pathNode);
		pathNode->path = true;
		pathNode = pathNode->parent;
	}

	std::reverse(path.begin(), path.end());

	return path;
}

std::vector<Cell*> GridManager::Djikstras(Cell* start, Cell* end)
{
	for (std::vector<Cell*> row : gridCells)
	{
		for (Cell* cell : row)
		{
			cell->distance = DBL_MAX;
			cell->parent = nullptr;
			cell->visited = false;
		}
	}

	std::queue<Cell*> searchQueue;

	start->startPoint = true;
	end->endPoint = true;
	start->distance = 0.0f;

	searchQueue.push(start);
	bool found = false;
	while (!searchQueue.empty())
	{
		Cell* current = searchQueue.front();
		searchQueue.pop();

		for (Cell* neighbour : current->neighbours)
		{
			if (neighbour == nullptr) continue;

			double tentantive = current->distance + 1.0;

			if (neighbour->distance > tentantive)
			{
				neighbour->parent = current;
				neighbour->distance = current->distance + 1.0;
				if (neighbour == end)
				{
					found = true;
					break;
				}
				if (!neighbour->visited)
					searchQueue.push(neighbour);
			}
		}

		current->visited = true;

		if (found) break;
	}

	std::vector<Cell*> path;
	if (!found) return path;

	path.push_back(end);

	Cell* pathNode = end->parent;
	while (pathNode != nullptr)
	{
		path.push_back(pathNode);
		pathNode->path = true;
		pathNode = pathNode->parent;
	}

	std::reverse(path.begin(), path.end());

	return path;
}

std::vector<Cell*> GridManager::AStar(Cell* start, Cell* end)
{
	for (std::vector<Cell*> row : gridCells)
	{
		for (Cell* cell : row)
		{
			if (cell->type == 0)
			{

				cell->distance = DBL_MAX;
				cell->parent = nullptr;
				cell->visited = false;
			}
		}
	}

	auto cmp = [](Cell* left, Cell* right) { return left->distance > right->distance; };
	std::priority_queue<Cell*, std::vector<Cell*>, decltype(cmp)> searchQueue(cmp);

	start->startPoint = true;
	end->endPoint = true;
	start->distance = 0.0f;

	searchQueue.push(start);
	bool found = false;
	while (!searchQueue.empty())
	{
		Cell* current = searchQueue.top();
		searchQueue.pop();

		for (Cell* neighbour : current->neighbours)
		{
			if (neighbour == nullptr) continue;

			// f(n) = g(n) + h(n)
			double tentantive = (current->distance + 1.0) + Manhattan(neighbour, end);

			if (neighbour->distance > tentantive)
			{
				neighbour->parent = current;
				neighbour->distance = tentantive;
				if (neighbour == end)
				{
					found = true;
					break;
				}
				if (!neighbour->visited)
					searchQueue.push(neighbour);
			}
		}

		current->visited = true;

		if (found) break;
	}

	std::vector<Cell*> path;
	if (!found) return path;

	path.push_back(end);

	Cell* pathNode = end->parent;
	while (pathNode != nullptr)
	{
		path.push_back(pathNode);
		pathNode->path = true;
		pathNode = pathNode->parent;
	}

	std::reverse(path.begin(), path.end());

	return path;
}

int GridManager::Manhattan(Cell* start, Cell* end)
{
	int result = 0;

	result = abs((start->xPos - end->xPos)) + abs((start->yPos - end->yPos));

	return result;
}

void GridManager::Draw(sf::RenderWindow& window, sf::Vector2i& mousePos)
{
	for (std::vector<Cell*> row : gridCells)
	{
		for (Cell* cell : row)
		{
			if (mousePos.x >= (cell->xPos * cell->Width)
				&& mousePos.x < (cell->xPos * cell->Width) + cell->Width
				&& mousePos.y >= (cell->yPos * cell->Height)
				&& mousePos.y < (cell->yPos * cell->Height) + cell->Height)
			{
				cellShape.setFillColor(sf::Color::Red);
				cell->highlighted = true;
				//std::cout << cell->type;
			}
			else {
				cell->highlighted = false;
				cellShape.setFillColor(sf::Color::Transparent);

				for (Cell* neighbour : cell->neighbours) {
					if (neighbour == nullptr) continue;
					if (neighbour->highlighted)
					{
						cellShape.setFillColor(sf::Color::Yellow);
						break;
					}
				}
				//0 is blank space, 1 is wall
				if (cell->type == 0)
				{
					cellShape.setFillColor(sf::Color::Black);
				}

				if (cell->type == 1)
				{
					cellShape.setFillColor(sf::Color::Cyan);
				}

				if (cell->type == 2)
				{
					cellShape.setFillColor(sf::Color::Green);
				}

				if (cell->visited)
				{
					//cellShape.setFillColor(sf::Color::Black);
				}

				if (cell->endPoint)
				{
					cellShape.setFillColor(sf::Color::Green);
				}

				if (cell->startPoint)
				{
					cellShape.setFillColor(sf::Color::Magenta);
				}

				if (cell->path)
				{
					cellShape.setFillColor(sf::Color::Yellow);

				}




			}
			cellShape.setPosition(cell->xPos * cell->Width, cell->yPos * cell->Height);
			window.draw(cellShape);
		}
	}
}

void GridManager::Generate(sf::RenderWindow& window)
{
	srand(time(0));

	for (std::vector<Cell*> row : gridCells)
	{
		

		for (Cell* cell : row) 
		{
			if (cell->xPos > 10)
			{
				int x = rand();
				if (x / 1000 < 10)
					cell->type = 1;
			}
			else
				cell->type = 0;

			
			//std::cout << x << std::endl;;
		}
		
	}

	for (std::vector<Cell*> row : gridCells)
	{


		for (Cell* cell : row)
		{
			//if(cell->type==1)
		}

	}


}


Cell* Cell::GetNeighbour(int dir)
{
	return neighbours[dir];
}
