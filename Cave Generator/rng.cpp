#include "rng.h"

int rng::inrange(int low, int high)
{
	std::uniform_int_distribution<int> dist(low, high);
	return dist(rand);
}

rng::rng() :
rand(dev())
{
}

void rng::setSeed(int seed)
{
	rand.seed(seed);
}

void rng::randomizeSeed()
{
	rand.seed(dev());
}

unsigned rng::getRandom()
{
	return rand();
}
