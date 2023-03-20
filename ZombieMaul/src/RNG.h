
#ifndef _RNG_H_
#define _RNG_H_

#include <random>

class UniformDistributor
{
public:
    UniformDistributor(int start, int end);

    int GetRandomValue();

private:
    std::default_random_engine rng;
    std::uniform_int_distribution<int> distributor;
};

#endif // !_RNG_H_
