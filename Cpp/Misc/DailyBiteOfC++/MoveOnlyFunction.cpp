#include <cassert>
#include <functional>
#include <memory>
#include <print>

namespace
{
    struct X
    {
        void operation(int val)
        {
            std::println("X::operation({})", val);
        }
        int x;
    };
}

int main()
{

    // Won't compile: the lambda is not copy-constructible
    // std::function<void(void)> f1 = [anchor = std::make_unique<int>(10)]()
    // {
    //     std::println("f1: anchor = {}", *anchor);
    // };

    // OK
    std::move_only_function<void(void)> f2 = [anchor = std::make_unique<int>(20)]()
    {
        std::println("f2: anchor = {}", *anchor);
    };

    std::move_only_function<void(X &, int)> f3 = &X::operation;
    std::move_only_function<int(X &)> f4 = &X::x;
    X x{};
    x.x = 3;
    f3(x, 22);
    int y = f4(x);
    assert(y == 3);

    // Respect const-ness
    const std::move_only_function<void(void)> f5 = []() {};
    // f5(); // Cannot compile: can store, but cannot invoke non-const call on const object.
    const std::move_only_function<void(void) const> f6 = []() {};
    f6(); // OK
}
