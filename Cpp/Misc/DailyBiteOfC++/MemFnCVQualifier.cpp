#include <utility>
#include <print>

namespace
{
    class Qualified
    {
    public:
        void Fn()
        {
            std::println("Fn");
        }
        void Fn() const
        {
            std::println("Fn const");
        }
        void Fn() volatile
        {
            std::println("Fn volatile");
        }
        void Fn() const volatile
        {
            std::println("Fn const volatile");
        }
    };

    class MyClass
    {
    public:
        void Fn() &
        {
            std::println("Fn &");
        }
        void Fn() &&
        {
            std::println("Fn &&");
        }
        void Fn() const &
        {
            std::println("Fn const&");
        }
    };
}

int main()
{
    Qualified q{};
    q.Fn();                // Fn
    std::as_const(q).Fn(); // Fn const
    volatile Qualified qq{};
    qq.Fn();                // Fn volatile
    std::as_const(qq).Fn(); // Fn const volatile

    std::println("\n");

    MyClass a{};
    a.Fn();                // Fn &
    std::as_const(a).Fn(); // Fn const&
    MyClass{}.Fn();        // Fn &&
    std::move(a).Fn();     // Fn &&

    return 0;
}
