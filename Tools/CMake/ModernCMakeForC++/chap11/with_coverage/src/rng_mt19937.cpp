#include "rng_mt19937.hpp"
#include <random>

int MT19937RandomNumberGenerator::Get()
{
    std::mt19937 generator{};
    std::uniform_int_distribution distribution{1, 6};
    return distribution(generator);
}
