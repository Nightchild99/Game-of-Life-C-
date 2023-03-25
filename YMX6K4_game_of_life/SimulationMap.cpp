#include "SimulationMap.h"
#include <random>
#include <vector>
#include <string>
#include <iostream>

SimulationMap::SimulationMap(const int num) //constructor 1
	: mX(num)
	, mY(num)
{
	SetupMap(mX, mY);
}

SimulationMap::SimulationMap(const int num1, const int num2) //constructor 2
	: mX(num1)
	, mY(num2)
{
	SetupMap(mX, mY);
}

SimulationMap::SimulationMap(const int num, const double chance) //constructor 3
	: mX(num)
	, mY(num)
{
	SetupMap(mX, mY, chance);
}

SimulationMap::SimulationMap(const int num1, const int num2, const double chance) //constructor 4
	: mX(num1)
	, mY(num2)
{
	SetupMap(mX, mY, chance);
}

std::random_device rnd;
std::default_random_engine defrnd(rnd());
std::uniform_int_distribution<int> uni_dist(1, 10);

void SimulationMap::SetupMap(const int X, const int Y, const double chance) 
{
	for (int i = 0; i < X; ++i)
	{
		std::vector<int> rowVector;
		for (int j = 0; j < Y; ++j)
		{
			if (uni_dist(defrnd) <= chance * 10)
			{
				rowVector.push_back(1);
			}
			else
			{
				rowVector.push_back(0);
			}
		}
		mMap.push_back(rowVector);
	}
}

void SimulationMap::DisplaySimulation()
{
	for (auto& i : mMap)
	{
		for (auto& j : i)
		{
			if (j)
			{
				std::cout << std::to_string(j) + " ";
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

int SimulationMap::CheckNeighbours(const int X, const int Y)
{
	int neighbours = 0;

	if (X + 1 < mX && Y + 1 <= mY && mMap[X + 1][Y + 1]) //bottom right corner
	{
		++neighbours;
	}

	if (Y + 1 <= mX && mMap[X][Y + 1]) //right
	{
		++neighbours;
	}

	if (X - 1 >= 0 && Y + 1 < mY && mMap[X - 1][Y + 1]) //top right corner
	{
		++neighbours;
	}

	if (X - 1 >= 0 && mMap[X - 1][Y]) //top
	{
		++neighbours;
	}

	if (X - 1 >= 0 && Y - 1 >= 0 && mMap[X - 1][Y - 1]) //top left corner
	{
		++neighbours;
	}

	if (Y - 1 >= 0 && mMap[X][Y - 1]) //left
	{
		++neighbours;
	}

	if (X + 1 < mX && Y - 1 >= 0 && mMap[X + 1][Y - 1]) //bottom left corner
	{
		++neighbours;
	}

	if (X + 1 < mX && mMap[X + 1][Y]) //bottom
	{
		++neighbours;
	}
}

void SimulationMap::GenerationStep()
{
	CellDead = true;
	int neighbours = 0;
	std::vector<std::vector<int>> nextStep;

	for (int i = 0; i < mX; ++i)
	{
		std::vector<int> updatedRow;
		for (int j = 0; j < mY; ++j)
		{
			neighbours = CheckNeighbours(i, j);
			int cell = mMap[i][j];

			if (cell)
			{
				if (neighbours == 2 || neighbours == 3)
				{
					updatedRow.push_back(1);
					CellDead = false;
				}
				else
				{
					updatedRow.push_back(0);
				}
			}
			else
			{
				if (neighbours == 3)
				{
					updatedRow.push_back(1);
					CellDead = false;
				}
				else
				{
					updatedRow.push_back(0);
				}
			}
		}
		nextStep.push_back(updatedRow);
	}
	mMap = nextStep;
}