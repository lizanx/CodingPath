#include <ranges>
#include <print>
#include <forward_list>
#include <list>
#include <vector>

namespace
{
    constexpr inline bool g_FeatureEnabled = true;

    void Fn()
    {
        if constexpr (g_FeatureEnabled)
        {
            std::println("Feature enabled.");
        }
        else
        {
            std::println("Feature disabled.");
        }
    }

    auto GenericFn(auto x)
    {
        if constexpr (std::is_integral_v<decltype(x)>)
            return std::to_string(x);
        else if constexpr (std::is_floating_point_v<decltype(x)>)
            return static_cast<int64_t>(x);
        else
            return;
    }

    void CustomAlgorithm(auto &&rng)
    {
        using type = decltype(rng);
        if constexpr (std::ranges::random_access_range<type>)
            std::println("Random-access range.");
        else if constexpr (std::ranges::bidirectional_range<type>)
            std::println("Bi-directional range.");
        else
            std::println("Fallback generic range.");
    }
}

int main()
{
    Fn();

    std::println();

    static_assert(std::is_same_v<decltype(GenericFn(3)), std::string>);
    std::println("GenericFn(int) -> {}", GenericFn(3));
    static_assert(std::is_same_v<decltype(GenericFn(1.1)), int64_t>);
    std::println("GenericFn(double) -> {}", GenericFn(1.1));
    static_assert(std::is_same_v<decltype(GenericFn("hello")), void>);

    std::println();

    CustomAlgorithm(std::vector<int>{1, 2, 3});
    CustomAlgorithm(std::list<int>{1, 2, 3});
    CustomAlgorithm(std::forward_list<int>{1, 2, 3});

    return 0;
}
