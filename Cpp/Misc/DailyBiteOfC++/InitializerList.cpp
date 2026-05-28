#include <cassert>
#include <initializer_list>
#include <print>
#include <type_traits>
#include <vector>

namespace
{
    struct X
    {
        X(std::initializer_list<int>)
        {
            std::println("X::X(std::initializer_list<int>)");
        }

        X &operator=(std::initializer_list<int>)
        {
            std::println("X::operator=(std::initializer_list<int>)");
            return *this;
        }
    };

    void Fn(std::initializer_list<int>)
    {
        std::println("Fn(std::initializer_list<int>)");
    }

    struct Data
    {
        Data() = default;

        Data(const Data &other)
        {
            std::println("Data::Data(const Data& other)");
        }
    };
}

int main()
{
    {
        std::println("=== Init X ===");
        X x{1, 2, 3};
        x = {4, 5, 6};
    }

    {
        std::println("=== Fn ===");
        Fn({1, 2, 3});
    }

    {
        std::println("=== Bind to auto ===");
        auto x = {1, 2, 3};
        static_assert((std::is_same_v<decltype(x), std::initializer_list<int>>));
    }

    {
        std::println("=== Checking copy counts ===");
        Data a{}, b{};
        std::println("Construction via initializer_list:");
        std::vector<Data> vec1{a, b};
        std::println("Construction with copy-elision");
        std::vector<Data> vec2{Data{}, Data{}};
    }

    return 0;
}
