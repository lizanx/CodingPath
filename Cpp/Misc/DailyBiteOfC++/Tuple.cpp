#include <print>
#include <tuple>
#include <type_traits>
#include <vector>

namespace
{
    int add(int a, int b)
    {
        return a + b;
    }
}

int main()
{
    auto a = std::tuple{};
    static_assert(std::tuple_size_v<decltype(a)> == 0);

    // auto b = std::tuple{5, 11};
    auto b = std::make_tuple(5, 11);

    auto v = std::make_from_tuple<std::vector<int>>(b);
    if (v != std::vector<int>{11, 11, 11, 11, 11})
        std::println("Error vec!");

    int result = std::apply(add, b);
    if (result != 16)
        std::println("Error add!");

    constexpr size_t cnt = std::tuple_size_v<decltype(b)>;
    static_assert(cnt == 2);
    using first_element_of_b_t = std::tuple_element_t<0, decltype(b)>;
    static_assert(std::is_same_v<first_element_of_b_t, int>);
    auto e = std::get<0>(b);
    static_assert(std::is_same_v<decltype(e), std::tuple_element_t<0, decltype(b)>>);

    int x{7}, y{42};
    auto t1 = std::make_tuple(x, y);
    static_assert(std::is_same_v<decltype(t1), std::tuple<int, int>>);
    auto t2 = std::make_tuple(std::ref(x), y);
    static_assert(std::is_same_v<decltype(t2), std::tuple<int &, int>>);
    auto t3 = std::make_tuple(std::ref(x), std::cref(y));
    static_assert(std::is_same_v<decltype(t3), std::tuple<int &, const int &>>);
    auto t4 = std::forward_as_tuple(std::move(x), std::move(y));
    static_assert(std::is_same_v<decltype(t4), std::tuple<int &&, int &&>>);
    auto t5 = std::forward_as_tuple(x, std::move(y));
    static_assert(std::is_same_v<decltype(t5), std::tuple<int &, int &&>>);

    auto t = std::tuple{"Hello world", 42, &a};
    auto [msg, val, ptr] = t;
    static_assert(std::is_same_v<decltype(msg), const char *>);
    static_assert(std::is_same_v<decltype(val), int>);
    static_assert(std::is_same_v<decltype(ptr), std::tuple<> *>);
    std::println("Msg: {}, value: {}, ptr: {}", msg, val, static_cast<void *>(ptr));

    return 0;
}
