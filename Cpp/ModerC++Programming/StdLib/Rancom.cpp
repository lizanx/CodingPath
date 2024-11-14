#include <chrono>
#include <iostream>
#include <random>

int main()
{
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned seed2 = seed1 + 10000;
    std::seed_seq seedSequence{seed1, seed2};

    std::default_random_engine generator1{seed1};
    std::default_random_engine generator2{seedSequence};

    std::uniform_int_distribution<unsigned> distribution{0, 100};

    for (size_t i{}; i < 100; ++i)
        std::cout << distribution(generator1) << " ";

    std::cout << "\n-------------------------------------------------\n";

    for (size_t i{}; i < 100; ++i)
        std::cout << distribution(generator2) << " ";

    return EXIT_SUCCESS;
}