#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

int main()
{
    std::vector<int64_t> data{1, 2, 3, 4, 5, 6};

    // Left fold with initial value.
    // Unlike std::accumulate, the result type is based on the invocation result of
    // operation(init, elem), not the type of "init".
    auto a = std::ranges::fold_left(data, 10, std::plus{});
    assert((std::is_same_v<decltype(a), int64_t>));
    assert(a == 31);

    // Right fold, using the last element as initializer.
    // The result is a std::optional to accommodate empty ranges.
    auto b = std::ranges::fold_right_last(data, std::plus{});
    assert((std::is_same_v<decltype(b), std::optional<int64_t>>));
    assert(b.has_value());
    assert(b == 21);

    std::vector<int> emptyData{};
    auto c = std::ranges::fold_left_first(emptyData, std::plus{});
    assert((std::is_same_v<decltype(c), std::optional<int>>));

    return 0;
}
