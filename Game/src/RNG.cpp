#include "RNG.h"

static std::random_device rd;

UniformDistributor::UniformDistributor(int start, int end) :
	mRng(rd()),
	mDistributor(start, end)
{}

int UniformDistributor::GetRandomValue() {
	return mDistributor(mRng);
}
