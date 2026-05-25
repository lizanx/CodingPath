#include <cassert>
#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> data{5, 1, 2, 4, 3};
    auto funcMedian = [](int a, int b, int c)
    {
        if (a >= b)
        {
            if (b >= c)
                return b;
            if (a >= c)
                return c;
            return a;
        }
        else
        {
            if (c >= b)
                return b;
            if (c >= a)
                return c;
            return a;
        }
    };
    {
        auto medians = data | std::views::adjacent_transform<3>(funcMedian);
        std::print("Medians: ");
        for (int n : medians)
            std::print("{} ", n);
        std::println();

        auto medianTwoSteps = data | std::views::adjacent<3> | std::views::transform([&](auto &&e)
                                                                                     { return std::apply(funcMedian, e); });
        std::print("Medians(2 steps): ");
        for (int n : medianTwoSteps)
            std::print("{} ", n);
        std::println();
    }
    {
        auto adjacentDiff = data | std::views::pairwise_transform(std::minus<>{});
        std::print("Adjacent differences: ");
        for (int n : adjacentDiff)
            std::print("{} ", n);
        std::println();

        auto adjacentDiff2 = data | std::views::adjacent_transform<2>(std::minus<>{});
        std::print("Adjacent differences(2): ");
        for (int n : adjacentDiff)
            std::print("{} ", n);
        std::println();
    }

    return 0;
}
