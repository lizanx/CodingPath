#include <cassert>
#include <cmath>
#include <numeric>
#include <print>
#include <vector>

int main()
{
    auto m1 = std::midpoint(std::numeric_limits<int>::max(), std::numeric_limits<int>::max() - 2);
    assert(m1 == std::numeric_limits<int>::max() - 1);

    int data[] = {5, 9, 2, 3, 1, 8, 4, 6, 7};
    auto m2 = std::midpoint(data, data + 9);
    assert(*m2 == 1);

    auto m3 = std::midpoint(3.2, 7.6);
    assert(std::fabs(m3 - 5.4) < 0.00001);

    std::vector<int> vec{1, 2, 3, 4, 5};
    auto m4 = std::midpoint(vec.data(), vec.data() + vec.size() - 1);
    assert(*m4 == 3);

    return 0;
}
