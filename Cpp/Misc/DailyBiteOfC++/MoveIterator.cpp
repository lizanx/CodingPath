#include <algorithm>
#include <cassert>
#include <iterator>
#include <list>
#include <print>
#include <ranges>
#include <vector>

namespace
{
    class Cls
    {
    public:
        Cls();
        Cls(std::string_view sv);
        Cls(const Cls &other);
        Cls(Cls &&other) noexcept;
        Cls &operator=(const Cls &other);
        Cls &operator=(Cls &&other) noexcept;

        std::string_view GetData() const;

    private:
        std::string m_data;
    };

    Cls::Cls() : Cls{""}
    {
    }

    Cls::Cls(std::string_view sv) : m_data{sv}
    {
    }

    Cls::Cls(const Cls &other) : m_data{other.m_data}
    {
        std::println("Copy ctor");
    }

    Cls::Cls(Cls &&other) noexcept : m_data{std::move(other.m_data)}
    {
        std::println("Move ctor");
    }

    Cls &Cls::operator=(const Cls &other)
    {
        m_data = other.m_data;
        std::println("Copy assignment");
        return *this;
    }

    Cls &Cls::operator=(Cls &&other) noexcept
    {
        m_data = std::move(other.m_data);
        std::println("Move assignment");
        return *this;
    }

    std::string_view Cls::GetData() const
    {
        return m_data;
    }
}

int main()
{
    std::vector<Cls> vec(4);
    vec.emplace_back("C++");
    vec.emplace_back("C");
    vec.emplace_back("C#");
    vec.emplace_back("Python");

    // Copy
    std::println("<<< anotherVec via copy >>>");
    std::vector<Cls> anotherVec{};
    anotherVec.reserve(vec.size());
    std::copy(std::begin(vec), std::end(vec), std::back_inserter(anotherVec));
    {
        auto iter = std::begin(anotherVec);
        assert(iter->GetData() == "C++");
        iter = std::next(iter);
        assert(iter->GetData() == "C");
        iter = std::next(iter);
        assert(iter->GetData() == "C#");
        iter = std::next(iter);
        assert(iter->GetData() == "Python");
    }
    std::println("After done:");
    for (const auto &cls : vec)
        std::println("\tData: {} ", cls.GetData());

    // Move
    std::println("<<< lst via move >>>");
    std::list<Cls> lst{};
    std::copy(std::make_move_iterator(std::begin(vec)), std::make_move_iterator(std::end(vec)), std::back_inserter(lst));
    {
        auto iter = std::begin(lst);
        assert(iter->GetData() == "C++");
        iter = std::next(iter);
        assert(iter->GetData() == "C");
        iter = std::next(iter);
        assert(iter->GetData() == "C#");
        iter = std::next(iter);
        assert(iter->GetData() == "Python");
    }
    std::println("After done:");
    for (const auto &cls : vec)
        std::println("\tData: {} ", cls.GetData());
}
