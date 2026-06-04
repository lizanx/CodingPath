#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <print>

namespace
{
    void Fn(int, int, int, int, int)
    {
        std::println("::Fn");
    }

    struct A
    {
        A(int, int, int, int, int)
        {
            std::println("A::A()");
        }
    };
}

int main()
{
    std::array<int, 5> data{1, 2, 3, 4, 5};

    std::ranges::sort(data, std::greater<>{});
    for (size_t i{}; i < data.size(); ++i)
        assert(data[i] == 5 - i);

    int x = std::get<2>(data);
    assert(x == 3);

    size_t sz = std::tuple_size<decltype(data)>{};
    assert(sz == 5);

    auto [a, b, c, d, e] = data;
    assert((a == 5 && b == 4 && c == 3 && d == 2 && e == 1));

    A m = std::make_from_tuple<A>(data);

    std::apply(Fn, data);

    return 0;
}
