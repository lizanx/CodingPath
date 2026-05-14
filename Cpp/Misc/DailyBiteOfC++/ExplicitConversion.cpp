#include <print>

namespace
{
    class Unsafe
    {
    public:
        Unsafe(int v) : m_value{v}
        {
        }

        operator int()
        {
            return m_value;
        }

    private:
        int m_value{};
    };

    class Safe
    {
    public:
        explicit Safe(int v) : m_value{v}
        {
        }

        explicit operator int()
        {
            return m_value;
        }

    private:
        int m_value{};
    };

    void Function(Unsafe, int)
    {
        std::println("f(Unsafe, int)");
    }

    void Function(Safe, int)
    {
        std::println("f(Safe, int)");
    }
}

int main()
{
    int value{10};
    Unsafe us{20};
    Safe s{30};

    Function(value, us); // silient error

    Function(value, s);            // cannot compile!!!
    Function(Safe{value}, int{s}); // must be explicit

    return 0;
}
