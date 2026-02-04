#pragma once

#include <random>

class UniformDistributor {
public:
	UniformDistributor(int start, int end);

	int GetRandomValue();

private:
	std::default_random_engine mRng;
	std::uniform_int_distribution<int> mDistributor;
};
