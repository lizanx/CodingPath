#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

int main()
{
    {
        std::vector<int> nonSorted{1, 2, 3, 4, 5, 2, 7, 8, 9};

        auto r1 = std::is_sorted(nonSorted.begin(), nonSorted.end());
        assert(r1 == false);

        auto r2 = std::is_sorted_until(nonSorted.begin(), nonSorted.end());
        assert(r2 == nonSorted.begin() + 5);
        assert(*r2 == 2);
    }

    {
        std::vector<std::string> sorted{"x", "mn", "xyz", "ijkl", "abcde"};

        auto r3 = std::ranges::is_sorted(sorted, [](const std::string &a, const std::string &b)
                                         { return a.length() < b.length(); });
        assert(r3 == true);

        auto r4 = std::ranges::is_sorted_until(sorted, [](const std::string &a, const std::string &b)
                                               { return a.length() < b.length(); });
        assert(r4 == sorted.end());
    }

    return 0;
}
