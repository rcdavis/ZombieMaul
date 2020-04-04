
#include "RNG.h"

static std::random_device rd;

UniformDistributor::UniformDistributor(int start, int end) :
	rng(rd()),
	distributor(start, end)
{}

int UniformDistributor::GetRandomValue()
{
	return distributor(rng);
}