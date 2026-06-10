#include <cassert>
#include <functional>
#include <print>

namespace
{
    void DemoSimple()
    {
        std::println(">>> DemoSimple <<<");

        auto zeroArg = []()
        {
            std::println("Calling 'zeroArg'");
        };

        auto twoArg = [](int x, int y)
        {
            std::println("Calling 'twoArg' with {} and {}", x, y);
            return x + y;
        };

        std::invoke(zeroArg);
        auto res = std::invoke(twoArg, 1, 2);
        assert(res == 3);

        std::println("<<< DemoSimple >>>\n");
    }

    void DemoMembers()
    {
        std::println(">>> DemoMembers <<<");

        struct X
        {
            int m_value;
            int GetValue() const
            {
                return m_value;
            }
            int Add(int extra) const
            {
                return m_value + extra;
            }
        };

        X x{42};
        auto a = std::invoke(&X::m_value, x);
        assert(a == 42);
        auto b = std::invoke(&X::GetValue, x);
        assert(b == 42);
        auto c = std::invoke(&X::Add, x, 20);
        assert(c == 62);

        std::println("a = {}, b = {}, c = {}", a, b, c);

        std::println("<<< DemoMembers >>>\n");
    }

    int DoSomeMagic(int a, int b)
    {
        return a + b;
    }
    // Dynamic type-erased 'std::move_only_function'.
    void Operate(int a, int b, std::move_only_function<void(std::string)> logger)
    {
        int c = DoSomeMagic(a, b);
        logger(std::format("Did some magic with {} and {}, the result is {}.", a, b, c));
    }
    // Statically customizing with a callable.
    void OperateStatic(int a, int b, auto &&logger)
    {
        int c = DoSomeMagic(a, b);
        std::invoke(std::forward<decltype(logger)>(logger),
                    std::format("Did some magic with {} and {}, the result is {}.", a, b, c));
    }
    void DemoAlternativeToStdFunction()
    {
        std::println(">>> DemoAlternativeToStdFunction <<<");

        auto logger1 = [](const std::string &msg)
        {
            std::println("Logger1: {}", msg);
        };
        auto logger2 = [](const std::string &msg)
        {
            std::println("Logger2: {}", msg);
        };

        Operate(1, 2, logger1);
        Operate(1, 2, logger2);

        OperateStatic(3, 4, logger1);
        OperateStatic(3, 4, logger2);

        std::println("<<< DemoAlternativeToStdFunction >>>\n");
    }
}

int main()
{
    DemoSimple();
    DemoMembers();
    DemoAlternativeToStdFunction();

    return 0;
}
