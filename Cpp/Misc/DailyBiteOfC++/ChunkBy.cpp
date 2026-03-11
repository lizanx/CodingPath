#include <cmath>
#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> data{-1, -2, -3, 4, 5, 6, -7, -8, -9, 10, 11};
    auto sameSign = [](int left, int right)
    {
        return std::signbit(left) == std::signbit(right);
    };

    for (const auto &chunk : std::views::chunk_by(data, sameSign))
    {
        std::println("Chunk:");
        for (int n : chunk)
        {
            std::println("\t{}", n);
        }
    }

    return 0;
}
