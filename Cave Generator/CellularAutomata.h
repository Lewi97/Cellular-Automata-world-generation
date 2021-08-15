#pragma once

#include <vector>

#include "rng.h"

// TODO
/*
Smoothing function, goes over all the tiles and changes them into the most common surrounding tile
*/

class CellularAutomata
{
private:
	// rng
	rng generator;

protected:
	int width = 124, height = 72;

	// world data
	std::vector<char> world;
	std::vector<char> nextworld;

	// functions
	// tools
	int toID(int x, int y);
	void finalizeworld(); // copies nextworld into world
	bool isSurrounded(int x, int y);  // checks if a cell is surrounded
	bool nearEmptyCell(int x, int y); // checks if a cell is near an empty cell
	int mostCommonNeighbour(int x, int y); // find most significant neighbour
									  
	// virtual functions
	// tools
	virtual int getneighbours(int x, int y); // grabs a cells neighbours

public:
	// Constructor
	CellularAutomata(int width, int height);
	
	// tools
	void smoothWorld();
	void removeSinglePixels(); // removes single cells with no neighbours
	void createworld(short walldensity = 45, unsigned seed = 0); // creates a randomized grid of cells with a fill parameter
	
	// virtual functions
	void iterateworld(int n); // iterates the world

	// Decorator
	virtual void decorator(); // Decorates the cells with more detail

	// getters
	std::vector<char>* getWorld(); // returns a pointer to the vector holding the world data
};

