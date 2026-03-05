#include <algorithm>
#include <cassert>
#include <execution>
#include <print>
#include <vector>
#include <optional>

namespace
{
    struct Stateful
    {
        int sum{};

        void operator()(int &n)
        {
            sum += n;
            ++n;
        }
    };

    struct Custom
    {
        static int Count;

        int ID;

        Custom() : ID{Count++} {}
    };

    int Custom::Count{};
}

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5};

    std::for_each(data.begin(), data.end(), [](int &n)
                  { ++n; });
    assert((data == std::vector<int>{2, 3, 4, 5, 6}));

    auto result = std::for_each(data.begin(), data.end(), Stateful{});
    assert(result.sum == 20);
    assert((data == std::vector<int>{3, 4, 5, 6, 7}));

    auto processCustom = [](Custom &custom)
    {
        std::println("{}", custom.ID);
    };
    std::vector<Custom> customData(10);
    std::for_each(std::execution::par_unseq, customData.begin(), customData.end(), processCustom);

    std::println("\nRange version with projection");
    std::vector<std::optional<int>> optData{{}, 2, {}, 4, {}};
    // Range version with projection
    std::ranges::for_each(optData, [](int n)
                          { std::println("Opt data: {}", n); }, [](std::optional<int> &opt)
                          { return opt.value_or(0); });

    return 0;
}
