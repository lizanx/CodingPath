#include <cassert>
#include <generator>
#include <iostream>
#include <utility>

namespace
{
    class EraseOnMove
    {
    public:
        EraseOnMove(int value);
        EraseOnMove(const EraseOnMove &) = default;
        EraseOnMove(EraseOnMove &&) noexcept;
        EraseOnMove &operator=(const EraseOnMove &) = default;
        EraseOnMove &operator=(EraseOnMove &&) noexcept;

        int GetValue() const noexcept;

    private:
        int m_value{};
    };

    EraseOnMove::EraseOnMove(int value) : m_value{value}
    {
    }

    EraseOnMove::EraseOnMove(EraseOnMove &&other) noexcept
    {
        m_value = std::exchange(other.m_value, 0);
    }

    EraseOnMove &EraseOnMove::operator=(EraseOnMove &&other) noexcept
    {
        m_value = std::exchange(other.m_value, 0);
        return *this;
    }

    int EraseOnMove::GetValue() const noexcept
    {
        return m_value;
    }

    void UseCase1()
    {
        EraseOnMove a{10};
        EraseOnMove b{std::move(a)};
        assert(a.GetValue() == 0);
        assert(b.GetValue() == 10);
        EraseOnMove c{5};
        c = EraseOnMove{2};
        assert(c.GetValue() == 2);
    }

    std::generator<int> Fibonacci(size_t cnt)
    {
        int a{}, b{1};
        while (cnt > 0)
        {
            co_yield std::exchange(a, std::exchange(b, a + b));
            --cnt;
        }
    }

    void UseCase2()
    {
        std::string delimiter{};
        for (int n : Fibonacci(10))
            std::cout << std::exchange(delimiter, ", ") << n;
        std::cout << "\n";
    }
}

int main()
{
    UseCase1();
    UseCase2();

    return 0;
}
