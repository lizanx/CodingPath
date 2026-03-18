#include <cassert>
#include <utility>

namespace
{
    template <typename TFunc, typename TArg>
    auto Fn1(TFunc fn, TArg &&arg)
    {
        return fn(std::forward<TArg>(arg));
    }

    template <typename TFunc, typename TArg>
    auto Fn2(TFunc &fn, TArg &&arg)
    {
        return fn(std::forward<TArg>(arg));
    }

    template <typename TFunc, typename TArg>
    auto Fn3(TFunc *fn, TArg &&arg)
    {
        return (*fn)(std::forward<TArg>(arg));
    }

    int AddTwo(int n)
    {
        return n + 2;
    }
}

int main()
{
    int a = Fn1(AddTwo, 1);
    assert(a == 3);
    int b = Fn2(AddTwo, 2);
    assert(b == 4);
    int c = Fn3(AddTwo, 3);
    assert(c == 5);

    return 0;
}
