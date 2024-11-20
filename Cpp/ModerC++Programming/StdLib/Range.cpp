#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

static auto SumOfSquares(int count)
{
    auto squares = std::ranges::iota_view{1, count} |
                   std::views::transform([](int i)
                                         { return i * i; });
    return std::accumulate(squares.begin(), squares.end(), 0);
}

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6};

    auto vec_view = std::views::all(vec);
    std::cout << "View: ";
    for (auto e : vec_view)
        std::cout << e << " ";
    std::cout << "\n";

    std::cout << "Reversed view: ";
    for (auto e : vec | std::views::reverse)
        std::cout << e << " ";
    std::cout << "\n";

    std::cout << "Reversed dropped view: ";
    auto reversed_dropped_view = vec | std::views::reverse | std::views::drop(2);
    for (auto e : reversed_dropped_view)
        std::cout << e << " ";
    std::cout << "\n";

    std::cout << "Range factory iota{1, 5}: ";
    for (int i : std::ranges::iota_view{1, 5})
        std::cout << i << " ";
    std::cout << "\n";

    std::cout << "Sum of squares from 1 to 10: " << SumOfSquares(10) << "\n";
}