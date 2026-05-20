#include <algorithm>
#include <cassert>
#include <vector>

int main()
{
    auto isEven = [](int n)
    { return n % 2 == 0; };

    {
        std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto iter = std::partition(data.begin(), data.end(), isEven);
        assert(iter != data.end());
        assert(std::all_of(data.begin(), iter, isEven));
        assert(!std::any_of(iter, data.end(), isEven));
    }

    {
        std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto iter = std::stable_partition(data.begin(), data.end(), isEven);
        assert(iter != data.end());
        assert(data[0] == 2);
        assert(data[1] == 4);
        assert(data[2] == 6);
        assert(data[3] == 8);
        assert(data[4] == 1);
        assert(data[5] == 3);
        assert(data[6] == 5);
        assert(data[7] == 7);
        assert(data[8] == 9);
    }

    return 0;
}
