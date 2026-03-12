#include <cassert>
#include <utility>

namespace
{
    struct OldStyleFunc
    {
        auto operator()(auto &&v) const
        {
            return std::forward<decltype(v)>(v);
        }
    };

    struct NewStyleFunc
    {
        static auto operator()(auto &&v)
        {
            return std::forward<decltype(v)>(v);
        }
    };

    constexpr auto g_oldStyle = OldStyleFunc{};
    constexpr auto g_newStyle = NewStyleFunc{};
}

int main()
{
    // Will pass both &g_oldStyle and 10
    int a = g_oldStyle(10);
    // Will pass only 10
    int b = g_newStyle(10);

    // Compiling error: cannot convert a member function to a function pointer
    // int (*p1)(int &&) = &OldStyleFunc::operator();

    // OK: member function -> member function pointer
    int (OldStyleFunc::*p2)(int &&) const = &OldStyleFunc::operator();
    int c = (g_oldStyle.*p2)(10);

    // OK: static member function -> function pointer
    int (*p3)(int &&) = &NewStyleFunc::operator();
    int d = p3(10);

    assert(a == 10);
    assert(b == 10);
    assert(c == 10);
    assert(d == 10);

    return 0;
}
