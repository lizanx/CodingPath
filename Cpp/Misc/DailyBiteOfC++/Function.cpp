#include <cassert>
#include <functional>
#include <memory>

namespace
{
    struct Func
    {
        int x{};
        void operator()()
        {
            ++x;
        }
    };
}

int main()
{
    const Func f1{};
    f1(); // cannot compile: "operator()" is not "const"

    // Despite following value semantics,
    // "std::function" doesn't respect "const".
    const std::function<void()> mutates = Func{};
    mutates(); // OK
    assert(mutates.target<Func>()->x == 1);

    auto f2 = [ptr = std::make_unique<int>(10)](int value)
    {
        return *ptr + value;
    };
    // Cannot compile: the stored object has to be copyable.
    // However, the lambda captures a "std::unique_ptr" which makes it move-only.
    std::function<int(int)> func = f2;

    return 0;
}
