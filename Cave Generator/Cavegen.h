#pragma once

#include "CellularAutomata.h"

class Cavegen : public CellularAutomata
{
public:
	using CellularAutomata::CellularAutomata;
	void decorator() override;
};

