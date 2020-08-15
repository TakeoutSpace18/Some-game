#pragma once
#include <random>

namespace Random
{
	static std::random_device rd;
	static std::mt19937 engine;

	static void init()
	{
		engine = std::mt19937(rd());
	}

	static int IntInRange(int low, int high)
	{
		std::uniform_int_distribution<int> dist(low, high);
		return dist(engine);
	}
}
