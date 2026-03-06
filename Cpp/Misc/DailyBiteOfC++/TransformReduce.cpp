#include <cassert>
#include <execution>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> v1{1, 2, 3}, v2{4, 5, 6};

    // 0 + (1*1) + (2*2) + (3*3)
    int res1 = std::transform_reduce(v1.begin(), v1.end(), 0, std::plus{}, [](int n)
                                     { return n * n; });
    assert(res1 == 14);

    // 2 + (4-1) + (5-2) + (6-3)
    int res2 = std::transform_reduce(v1.begin(), v1.end(), v2.begin(), 2, std::plus{}, [](int m, int n)
                                     { return n - m; });
    assert(res2 == 11);

    return 0;
}
