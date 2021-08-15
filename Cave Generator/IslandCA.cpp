#include "IslandCA.h"

int IslandCA::getneighbours(int x, int y)
{
	int n = 0;

	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0) continue;
			if (x + i > this->width - 1 || y + j > this->height - 1 || y + j < 0 || x + i < 0) continue;
			if (world[toID(x + i, y + j)] > 0)
				n++;
		}

	return n;
}

