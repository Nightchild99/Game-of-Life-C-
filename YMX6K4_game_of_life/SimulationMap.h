#pragma once
#include <iostream>
#include <vector>

class SimulationMap {

public:
	bool CellDead;

	SimulationMap(const int X);
	SimulationMap(const int X, const int Y);
	SimulationMap(const int X, const double chance);
	SimulationMap(const int X, const int Y, const double chance);
	SimulationMap(const int Height, const int Width, const int Top, const int Left, std::vector<std::vector<int>> lilMap);

	void SetupMap(const int X, const int Y, const double Prob = 0.1);

	void GenerationStep();

	int CheckNeighbours(const int i, const int j);

	void DisplaySimulation();

private:
	int mX;
	int mY;
	std::vector<std::vector<int>> mMap;
};
