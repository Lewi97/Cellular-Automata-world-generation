#include "Cavegen.h"
/*
int Cavegen::toID(int x, int y)
{
	return x + this->width * y;
}

void Cavegen::finalizeworld()
{
	world = nextworld;
}

int Cavegen::getneighbours(int x, int y)
{
	int n = 0;

	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0) continue;
			if (x + i > this->width - 1 || y + j > this->height - 1 || y + j < 0 || x + i < 0) { n++; continue; }
			n += world[toID(x + i, y + j)];
		}

	return n;
}

Cavegen::Cavegen(int width, int height) :
	width(width), height(height)
{
	for (int x = 0; x < width * height; x++)
	{
		world.emplace_back(0);
		nextworld.emplace_back(0);
	}
	
	createworld();
}

void Cavegen::removeSinglePixels()
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (getneighbours(x, y) == 0)
				nextworld[toID(x, y)] = 0;

	finalizeworld();
}

void Cavegen::iterateworld(int n)
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			int neighbours = getneighbours(x, y);
			if (neighbours < n)
				nextworld[toID(x, y)] = 0;
			else if (neighbours > n)
				nextworld[toID(x, y)] = 1;
		}

	finalizeworld();
}

void Cavegen::createworld(short walldensity)
{
	for (int i = 0; i < height * width; i++)
		this->world[i] = this->generator.inrange(1, 100) > walldensity ? 0 : 1;
}

std::vector<char>& Cavegen::getWorld()
{
	return this->world;
}
*/

void Cavegen::decorator()
{
	
}

int Cavegen::getneighbours(int x, int y)
{
	int n = 0;

	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{

			if (i == 0 && j == 0) continue;
			if (x + i > this->width - 1 || y + j > this->height - 1 || y + j < 0 || x + i < 0) { n++; continue; }
			n += world[toID(x + i, y + j)];
		}

	return n;
}
