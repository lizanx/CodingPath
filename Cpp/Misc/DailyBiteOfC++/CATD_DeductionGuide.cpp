#include <string>
#include <type_traits>
#include <vector>
#include <iterator>

namespace
{
    template <typename T>
    struct Storage
    {
        Storage(T t) : m_t{t} {}

        T m_t;
    };

    Storage(const char *) -> Storage<std::string>;

    template <typename T1, typename T2>
    struct Pair
    {
        Pair(T1 t1, T2 t2) : m_t1{t1}, m_t2{t2} {}

        // Not a valid ctor without deduction guide
        Pair(T1 t) : m_t1{t} {}

        T1 m_t1{};
        T2 m_t2{};
    };

    // Must exist for the second ctor to be legal.
    template <typename T>
    Pair(T) -> Pair<T, T>;
}

int main()
{
    Storage s1{10};
    static_assert(std::is_same_v<decltype(s1), Storage<int>>);

    Storage s2{"Hello"};
    static_assert(std::is_same_v<decltype(s2), Storage<std::string>>);

    Pair p1{1, 2.0};
    static_assert(std::is_same_v<decltype(p1), Pair<int, double>>);

    Pair p2{2};
    static_assert(std::is_same_v<decltype(p2), Pair<int, int>>);

    return 0;
}
