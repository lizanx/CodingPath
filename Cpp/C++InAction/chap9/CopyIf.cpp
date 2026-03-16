#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector src{1, 2, 3, 4, 5, 6};
    std::vector<int> dst{};

    // Only copy elements with even index.
    std::copy_if(src.begin(), src.end(), std::back_inserter(dst), [flag = false](int) mutable
                 {
        flag = !flag;
        return flag; });

    std::copy(dst.begin(), dst.end(), std::ostream_iterator<int>{std::cout, ", "});

    return 0;
}
