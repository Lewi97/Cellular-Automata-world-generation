#pragma once

#include <random>

class rng
{
private:
	std::random_device dev;
	std::mt19937 rand;
public:
	rng();
	int inrange(int low, int high);
	void setSeed(int seed);
	void randomizeSeed();
	unsigned getRandom();
};

