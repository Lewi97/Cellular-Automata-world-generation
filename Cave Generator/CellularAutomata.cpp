#include "CellularAutomata.h"

int CellularAutomata::toID(int x, int y)
{
	return x + this->width * y;
}

void CellularAutomata::finalizeworld()
{
	world = nextworld;
}

bool CellularAutomata::isSurrounded(int x, int y)
{
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;
			if (x + i > width - 1 || y + j > height - 1 || y + j < 0 || x + i < 0)
				continue;
			if (world[toID(x + i, y + j)] < 1)
				return false;
		}

	return true;
}

bool CellularAutomata::nearEmptyCell(int x, int y)
{
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;
			if (x + i > width - 1 || y + j > height - 1 || y + j < 0 || x + i < 0)
				return true;
			if (world[toID(x + i, y + j)] < 1)
				return true;
		}

	return false;
}

int CellularAutomata::mostCommonNeighbour(int x, int y)
{
	short n = getneighbours(x, y);

	return n == 4 ? world[toID(x,y)] : n > 4 ? 1 : 0;
}

CellularAutomata::CellularAutomata(int width, int height) :
	width(width), height(height)
{
	for (int x = 0; x < width * height; x++)
	{
		world.emplace_back(0);
		nextworld.emplace_back(0);
	}

	createworld();
}

void CellularAutomata::smoothWorld()
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			nextworld[toID(x, y)] = mostCommonNeighbour(x, y);

	finalizeworld();
}

void CellularAutomata::removeSinglePixels()
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (getneighbours(x, y) == 0)
				nextworld[toID(x, y)] = 0;

	finalizeworld();
}

void CellularAutomata::applyRules(int n)
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

void CellularAutomata::decorator()
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			int ID = 0;

			if (world[toID(x, y)] == 0)
				ID = 0;
			else if (nearEmptyCell(x, y))
				ID = 1;
			else
				ID = 2;

			nextworld[toID(x, y)] = ID;
		}

	finalizeworld();
}

void CellularAutomata::createworld(short walldensity, unsigned seed)
{
	if (seed > 0)
		generator.setSeed(seed);
	//else
	//	generator.randomizeSeed();

	for (int i = 0; i < height * width; i++)
		this->world[i] = this->generator.inrange(1, 100) > walldensity ? 0 : 1;
}

std::vector<char>* CellularAutomata::getWorld()
{
	std::vector<char>* worldPointer = &world;
	return worldPointer;
}


