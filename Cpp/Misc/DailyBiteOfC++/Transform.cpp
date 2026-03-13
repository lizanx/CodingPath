#include <algorithm>
#include <cctype>
#include <iterator>
#include <print>
#include <string>
#include <vector>

namespace
{
    const std::vector<int> g_in{1, 2, 3, 4, 5, 6, 7};
    const std::vector<int> g_in1{1, 2, 3, 4, 5};
    const std::vector<int> g_in2{0, 1, 0, 1, 0};
}

int main()
{
    {
        std::vector<double> out{};
        std::transform(g_in.cbegin(), g_in.cend(), std::back_inserter(out), [](int n)
                       { return static_cast<double>(n) / 2; });
        std::println("out: {}", out);
    }

    {
        std::vector<int> reduction{};
        std::transform(g_in1.cbegin(), g_in1.cend(), g_in2.cbegin(), std::back_inserter(reduction), [](int n1, int n2)
                       { return n1 * n2; });
        std::println("reduction: {}", reduction);
    }

    {
        // The output range can be one of the input ranges.
        std::string str{"welcome to somewhere"};
        std::transform(str.begin(), str.end(), str.begin(), [](char c)
                       { return std::toupper(c); });
        std::println("str: {}", str);
    }

    {
        std::vector<int> twoDigits{};
        std::ranges::transform(g_in1, g_in2, std::back_inserter(twoDigits), std::plus{}, [](int n)
                               { return n * 10; }, std::identity{});
        std::println("twoDigits: {}", twoDigits);
    }

    return 0;
}
