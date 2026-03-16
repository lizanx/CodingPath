#include <algorithm>
#include <print>
#include <vector>

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};

    bool r1 = std::ranges::contains(data, 5);
    bool r2 = std::ranges::find(data, 5) != data.end();
    std::println("{} {}", r1, r2);

    std::vector<int> partial{1, 2, 3};
    bool r3 = std::ranges::contains_subrange(data, partial);
    bool r4 = not std::ranges::search(data, partial).empty();
    std::println("{} {}", r3, r4);

    return 0;
}
