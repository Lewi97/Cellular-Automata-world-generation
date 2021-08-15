#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "CellularAutomata.h"
#include "IslandCA.h"
#include "Cavegen.h"
#include "SeedWorld.h"

#define LOG(x) std::cout << x << std::endl;

constexpr int windowWidth = { 1240 };
constexpr int windowHeight = { 720 };

constexpr int gridsize = { 10 };

constexpr int simWidth = { windowWidth / gridsize };
constexpr int simHeight = { windowHeight / gridsize };

std::vector<sf::Vertex> quads;

int toID(int x, int y)
{
	return x + simWidth * y;
}

void batch(float x, float y)
{
	sf::Vertex topleft,topright,bottomleft,bottomright;

	topleft.position = { x * gridsize,y * gridsize };
	topright.position = { x * gridsize + gridsize,y * gridsize };
	bottomleft.position = { x * gridsize,y * gridsize + gridsize };
	bottomright.position = { x * gridsize + gridsize,y * gridsize + gridsize };
	
	quads.emplace_back(topleft);
	quads.emplace_back(topright);
	quads.emplace_back(bottomright);
	quads.emplace_back(bottomleft);
}

void colorquad(int index, sf::Color col)
{
	for (int i = 0; i < 4; i++)
		quads[index * 4 + i].color = col;
}

void colorquad(int x, int y, sf::Color col)
{
	for (int i = 0; i < 4; i++)
		quads[(x + simWidth * y) * 4 + i].color = col;
}

sf::Color determineColorIsland(char n)
{
	switch (n)
	{
	case 0:
		return sf::Color::Blue;
	case 1:
		return sf::Color::Yellow;
	case 2:
		return sf::Color::Green;
	}

	return sf::Color::White;
}

void colorGrid(const std::vector<char>& world, bool caves = true)
{
	if (caves)
		for (int i = 0; i < simWidth * simHeight; i++)
			colorquad(i, ((bool)world.at(i) ? sf::Color::Black : sf::Color::White));
	else
		for (int i = 0; i < simWidth * simHeight; i++)
			colorquad(i, determineColorIsland(world[i]));
}

void drawGrid(const std::vector<char>& world)
{
	for (int i = 0; i < simWidth * simHeight; i++)
		colorquad(i, ((bool)world.at(i) ? sf::Color::Black : sf::Color::White));
}

void writeConfigToConsole(short iterateCount, short wallDensity, short neighboursRequired, bool caves)
{
	system("cls");
	std::cout << "Iterations set to : " << iterateCount <<
				 "\nWall density : " << wallDensity <<
				 "\nCell life : " << neighboursRequired << 
				 "\nGenerating " << (caves ? "caves" : "islands") << std::endl;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "main");
	sf::Event event;
	//float delta;
	//sf::Clock dt;

	int iterateCount = 3;
	bool generateCaves = false;
	short wallDensity = 60;
	short neighboursRequired = 4;

	Cavegen* cave = new Cavegen(simWidth, simHeight);
	IslandCA* island = new IslandCA(simWidth, simHeight);
	SeedWorld seeds(simWidth, simHeight);

	CellularAutomata* CA = island;

	for (int y = 0; y < simHeight; y++)
		for (int x = 0; x < simWidth; x++)
			batch((float)x, (float)y);

	std::vector<char>* mapholder = CA->getWorld();
	CA->createworld(wallDensity);
	drawGrid(*mapholder);

	writeConfigToConsole(iterateCount, wallDensity, neighboursRequired, generateCaves);

	while (window.isOpen()) {
		// get delta time
		//delta = dt.restart().asSeconds();

		// TODO: turn more stuff into functions

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: window.close(); break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					CA->iterateworld(neighboursRequired);
					drawGrid(*mapholder);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					CA->createworld(wallDensity);

					for (int i = 0; i < iterateCount; i++)
						CA->iterateworld(neighboursRequired);

					CA->removeSinglePixels();
					drawGrid(*mapholder);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					++iterateCount;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					--iterateCount;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					CA->createworld(wallDensity, 250U);
					drawGrid(*mapholder);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					CA->smoothWorld();
					drawGrid(*mapholder);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				{
					generateCaves = !generateCaves;
					
					if (!generateCaves)
						CA = island;
					else
						CA = cave;

					mapholder = CA->getWorld();
					CA->createworld(wallDensity);
					drawGrid(*mapholder);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
					wallDensity--;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
					wallDensity++;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket))
					neighboursRequired++;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket))
					neighboursRequired--;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					CA->decorator();
					colorGrid(*mapholder, generateCaves);
				}
				writeConfigToConsole(iterateCount, wallDensity, neighboursRequired, generateCaves);
				break;
			case sf::Event::KeyReleased:
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i mouse = sf::Mouse::getPosition(window) / gridsize;
				/*if ((*mapholder)[mouse.x + simWidth * mouse.y] < 2) 
					break;
				generateCaves = true;
				CA = cave;
				mapholder = CA->getWorld();
				unsigned seed = seeds.getSeedFrom(mouse.x + simWidth * mouse.y);
				CA->createworld(wallDensity, seed);
				for (int i = 0; i < 5; i++)
					CA->iterateworld(neighboursRequired);
				colorGrid(*mapholder, generateCaves);*/
				break;
			}
		}

		window.clear(sf::Color::Black);

		window.draw(quads.data(), quads.size(), sf::Quads);

		window.display();

	}

	return 0;
}