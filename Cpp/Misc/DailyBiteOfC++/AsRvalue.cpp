#include <algorithm>
#include <print>
#include <ranges>
#include <utility>
#include <vector>

namespace
{
    class Data
    {
    public:
        Data(int value) : m_value{value}
        {
        }
        Data(const Data &other) : m_value{other.m_value}
        {

            std::println("Copy ctor");
        }
        Data(Data &&other) noexcept : m_value{std::exchange(other.m_value, 0)}
        {
            std::println("Move ctor");
        }
        Data &operator=(const Data &other)
        {
            m_value = other.m_value;
            std::println("Copy assignment");
            return *this;
        }
        Data &operator=(Data &&other) noexcept
        {
            m_value = std::exchange(other.m_value, 0);
            std::println("Move assignment");
            return *this;
        }

        int GetValue() const noexcept
        {
            return m_value;
        }

    private:
        int m_value;
    };

    void ViaCopy()
    {
        std::println("<<< ViaCopy >>>");
        std::vector<Data> vec{{1}, {2}, {3}};
        for (const auto &d : vec | std::views::transform([](const Data &data)
                                                         { return data; }))
        {
            std::println("{}", d.GetValue());
        }
    }

    void ViaMove()
    {
        std::println("<<< ViaMove >>>");
        std::vector<Data> vec{{1}, {2}, {3}};
        for (const auto &d : vec | std::views::as_rvalue | std::views::transform([](Data &&data)
                                                                                 { return std::forward<Data>(data); }))
        {
            std::println("{}", d.GetValue());
        }
    }
}

int main()
{
    ViaCopy();
    std::println("\n\n");
    ViaMove();

    return 0;
}
