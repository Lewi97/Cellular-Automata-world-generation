#include "SeedWorld.h"

void SeedWorld::populateWorld()
{
	for (int i = 0; i < width * height; i++)
		world.emplace_back(generator.getRandom());
}

SeedWorld::SeedWorld(int width, int height) :
	width(width),
	height(height)
{
	populateWorld();
}

void SeedWorld::randomize(unsigned seed)
{
	if (seed > 0)
		generator.setSeed(seed);
	
	populateWorld();
}

unsigned SeedWorld::getSeedFrom(int id)
{
	return world[id];
}
