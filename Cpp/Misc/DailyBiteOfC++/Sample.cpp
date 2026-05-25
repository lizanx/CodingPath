#include <algorithm>
#include <cassert>
#include <iterator>
#include <random>
#include <vector>

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};

    constexpr size_t SAMPLE_SIZE = 4;
    std::vector<int> out;
    out.reserve(SAMPLE_SIZE);

    auto gen = std::mt19937{1};
    std::sample(data.begin(), data.end(), std::back_inserter(out), SAMPLE_SIZE, gen);
    assert(out.size() == SAMPLE_SIZE);
    for (int n : out)
        assert(std::find(data.begin(), data.end(), n) != data.end());

    return 0;
}
