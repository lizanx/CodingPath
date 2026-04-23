// The Curious Recurring Template Pattern
#include <print>

namespace
{
    template <typename T>
    class Base
    {
    public:
        auto Foo() -> int
        {
            return 1 + static_cast<T *>(this)->Bar();
        }
    };

    class D1 : public Base<D1>
    {
    public:
        auto Bar() -> int
        {
            return 10;
        }
    };

    class D2 : public Base<D2>
    {
    public:
        auto Bar() -> int
        {
            return 20;
        }
    };

    template <typename T>
    void PrintValue(Base<T> &base)
    {
        std::println("Value: {}", base.Foo());
    }
}

int main()
{
    D1 d1{};
    D2 d2{};
    PrintValue(d1);
    PrintValue(d2);

    return 0;
}
