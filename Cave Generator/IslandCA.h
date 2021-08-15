#pragma once

#include "CellularAutomata.h"

class IslandCA : public CellularAutomata
{
public:
	using CellularAutomata::CellularAutomata;
	int getneighbours(int x, int y) override;
};

