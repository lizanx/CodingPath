#include <algorithm>
#include <concepts>
#include <print>
#include <ranges>
#include <vector>

namespace
{
    template <typename T>
    auto AbsoluteBase(T t)
    {
        if constexpr (requires(T t) {
                          { t.base() } -> std::same_as<typename T::iterator_type>;
                      })
            return AbsoluteBase(t.base());
        else
            return t;
    }
}

int main(int argc, char *argv[])
{
    std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};

    constexpr auto view = std::views::reverse | std::views::drop(3) | std::views::reverse;
    auto [iter, value] = std::ranges::fold_left_with_iter(data | view, 0, std::plus{});
    std::println("Sum of all but last three elements: {}", value);
    for (auto v : std::ranges::subrange(AbsoluteBase(iter), data.end()))
    {
        std::println("Dropped value: {}", v);
    }

    return 0;
}
