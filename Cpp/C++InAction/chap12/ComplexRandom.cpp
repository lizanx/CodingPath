#include <algorithm>
#include <array>
#include <execution>
#include <print>
#include <random>
#include <vector>

int main()
{
    std::random_device rd{};
    std::array<uint32_t, 8> seedData{};
    std::generate_n(seedData.begin(), seedData.size(), [&rd]()
                    { return rd(); });
    std::seed_seq seedSequence{seedData.begin(), seedData.end()};
    std::mt19937 gen{seedSequence};
    std::uniform_int_distribution dist{1, 1'000'000'000};
    std::vector<int> v(1'000'000);
    std::generate_n(v.begin(), v.size(), [&dist, &gen]()
                    { return dist(gen); });
    auto average = std::reduce(std::execution::par_unseq, v.begin(), v.end(), 0ULL, std::plus{});
    std::println("Average: {}", average / v.size());

    return 0;
}
