#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "BaseEntity.h"
#include "UtilRandom.h"
#include "Constants.h"
#include "GridManager.h"
#include "PathFinding.h"

#include "StateMachine.h"

#include "QuadTree.h"
#include "Boid.h"
#include "Seeker.h"

#include <float.h>
unsigned int current_word = 0;
unsigned int fp_control_state = _controlfp_s(&current_word, _EM_INEXACT, _MCW_EM);

int main()
{
	int sec; // variable that holds current second
	int aux=0; // variable used for the clock
	

	// construct a window
	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "AI Framework");

	// because we're running as a console application, we still get access to the console, so can use std::cout to print to it
	std::cout << "Constructed SFML Window" << std::endl;
	cout << "Time in seconds is: ";
	std::vector<BaseEntity*> entities;
	GridManager grid;

	StateMachine state; // create a state


	sf::Font font;
	font.loadFromFile("assets\\bahnschrift.ttf");

	sf::Text boidText;
	boidText.setFont(font);
	boidText.setCharacterSize(36);
	boidText.setFillColor(sf::Color::White);
	boidText.setStyle(sf::Text::Bold);

	sf::CircleShape highlight{ 125.0f };
	highlight.setOutlineColor(sf::Color::Red);
	highlight.setFillColor(sf::Color::Transparent);
	highlight.setOutlineThickness(1.0f);
	highlight.setOrigin(125, 125);

	for (int i = 0; i < MaxBoids; ++i)
	{
		Boid* temp = new Boid();
		temp->Initialize();
	}

	Seeker seek;
	seek.SetTextureFile("assets\\boid.png");
	seek.Initialize();


	auto currentBoid = BaseEntity::Renderables.front();

	currentBoid->SetColour(sf::Color::Red);
	currentBoid->Initialize();

	// we get some coordinates for the path to be assigned to
	int startX = UtilRandom::instance()->GetRange(0,9);
	int startY = UtilRandom::instance()->GetRange(0,6);

	int endX = UtilRandom::instance()->GetRange(startX,startX);
	int endY = UtilRandom::instance()->GetRange(startY+2,9);


	Cell* start = grid.FindGridCell(startX, startY);
	Cell* end = grid.FindGridCell(endX, endY);

	end->type = 0;
	
	// these coordinates are for showcasing path finding through a maze
	int startXpathDemo = UtilRandom::instance()->GetRange(10, grid.ColSize - 1);
	int startYpathDemo = UtilRandom::instance()->GetRange(0, grid.RowSize - 1);

	int endXpathDemo = UtilRandom::instance()->GetRange(10, grid.ColSize - 1);
	int endYpathDemo = UtilRandom::instance()->GetRange(0, grid.RowSize - 1);


	Cell* startDemo = grid.FindGridCell(startXpathDemo, startYpathDemo);
	Cell* endDemo = grid.FindGridCell(endXpathDemo, endYpathDemo);

	endDemo->type = 0;


	std::vector<Cell*> pathDemo = grid.AStar(startDemo, endDemo);
	std::vector<Cell*> path = grid.AStar(start, end);
	std::reverse(path.begin(),path.end()); // we reverse the vector to go through it as desired

	
	PathFinding PathAgent;
	

	PathAgent.SetTextureFile("assets\\circle - Copy.png"); // we initalize the path following agent
	PathAgent.Initialize();
	PathAgent.skipUpdate = 1;
	PathAgent.setPosition(0, 0);
	
	PathAgent.SetPath(path); // we set it's path

	
	grid.Generate(window); // we generate our window
	sf::Clock clock;
	string stateDetail = "default";
	
	// our game loop

	while (window.isOpen())
	{
		
		BaseEntity* dataAgent;
		// poll for events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					stateDetail = state.getStateName();
 					
				}
			}
		}
		
		sf::Time elapsed1 = clock.getElapsedTime(); // we get the current time then we store it as seconds
		sec = (int)elapsed1.asSeconds();
		

		
		if (sec == aux)
		{
			
			std::cout << sec << ", ";
			if (aux % 2 == 0)
			{
				state.Tick(aux); // we tick our state depending on the timer
				PathAgent.followPath(); // we also update the pathing of our agent depending on the timer

			}
			if (aux % 60 == 0)
			{
				cout << "\n\n\n" << aux / 60 << " minutes elapsed." << "\n";
				
			}

			aux++;
		}

		
		// clear the window before drawing anything to it
		window.clear();
		
		// update all our entities
		for ( auto entity : BaseEntity::Renderables )
		{
			entity->Think(); 
		}

		for (auto entity : BaseEntity::Renderables)
		{
			if(entity->skipUpdate ==0)
			entity->Update();
		}
		
		//quad.Draw(window);
		
		grid.Draw(window, sf::Mouse::getPosition(window));
		
		std::ostringstream data; // print some relevant data to the user
		data << "velocity: " << PathAgent.getVelocity().x << " " << PathAgent.getVelocity().y << "\n"
			<< "acceleration:" << PathAgent.getAcceleration().x << " " << PathAgent.getAcceleration().y << "\n"
			<< "Current state: " << stateDetail << "\n";
		

		boidText.setString(data.str());
		// and then draw them
		for (auto entity : BaseEntity::Renderables)
		{
			window.draw(entity->GetSprite(), entity->getTransform());

			if (entity == currentBoid)
			{
				highlight.setPosition(currentBoid->getPosition());
				window.draw(highlight);
			}

			

		}

		window.draw(boidText);

		// swap the frame buffers
		window.display();
	}

	return 0;
}
