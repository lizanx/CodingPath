#include <algorithm>
#include <print>
#include <vector>

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 6, 4, 5, 3, 3, 2, 8, 9, 7, 7};
    std::sort(std::begin(vec), std::end(vec));

    std::vector<int> result{};
    std::unique_copy(std::begin(vec), std::end(vec), std::back_inserter(result));
    std::println("Result:");
    for (const int n : result)
        std::println("\t{}", n);

    auto iter = std::unique(std::begin(vec), std::end(vec));
    vec.erase(iter, std::end(vec));
    std::println("\nVec:");
    for (const int n : vec)
        std::println("\t{}", n);
}
