#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto window : vec | std::views::slide(4))
    {
        std::print("Window: ");
        for (int n : window)
        {
            std::print("{} ", n);
        }
        std::println();
    }

    return 0;
}
