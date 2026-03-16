#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
    void Copy()
    {
        std::vector<int> v{1, 2, 3, 4, 5};
        // Undefined behavior!!!
        std::copy(v.begin(), v.begin() + 3, v.begin() + 2);

        std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, " "});
        std::cout << "\n";
    }

    void CopyBackward()
    {
        std::vector<int> v{1, 2, 3, 4, 5};
        // Well defined!
        std::copy_backward(v.begin(), v.begin() + 3, v.end());

        std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, " "});
        std::cout << "\n";
    }
}

int main()
{
    Copy();
    CopyBackward();

    return 0;
}
