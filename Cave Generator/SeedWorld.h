#pragma once

#include <vector>

#include "rng.h"

class SeedWorld
{
private:
	rng generator;
	int width = 124, height = 72;
	std::vector<unsigned> world;
	void populateWorld();
public:
	SeedWorld(int width, int height);
	void randomize(unsigned seed = 0U);
	unsigned getSeedFrom(int id);
};

