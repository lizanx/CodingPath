#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace
{
struct Foo
{
    std::string name;
    int a;
    int b;
    int c;
    int d;
};

template <typename T> bool Compare(auto &lhs, auto &rhs, auto T::*key, auto... keys)
{
    if (lhs.*key < rhs.*key)
        return true;
    if (lhs.*key > rhs.*key)
        return false;
    if constexpr (sizeof...(keys) > 0)
        return Compare(lhs, rhs, keys...);
    return false;
}

void Sort(auto &data, auto... keys)
{
    std::sort(std::begin(data), std::end(data), [keys...](auto &lhs, auto &rhs) { return Compare(lhs, rhs, keys...); });
}
} // namespace

int main()
{
    using namespace std::string_literals;
    std::vector<Foo> vec{};
    vec.emplace_back("A"s, 1, 4, 3, 4);
    vec.emplace_back("B"s, 2, 3, 4, 1);
    vec.emplace_back("C"s, 3, 2, 2, 2);
    vec.emplace_back("D"s, 4, 1, 2, 3);

    Sort(vec, &Foo::a);
    for (const auto &item : vec)
        std::cout << item.name;
    std::cout << "\n";

    Sort(vec, &Foo::b);
    for (const auto &item : vec)
        std::cout << item.name;
    std::cout << "\n";

    Sort(vec, &Foo::c);
    for (const auto &item : vec)
        std::cout << item.name;
    std::cout << "\n";

    Sort(vec, &Foo::d);
    for (const auto &item : vec)
        std::cout << item.name;
    std::cout << "\n";

    Sort(vec, &Foo::c, &Foo::d);
    for (const auto &item : vec)
        std::cout << item.name;
    std::cout << "\n";
}
