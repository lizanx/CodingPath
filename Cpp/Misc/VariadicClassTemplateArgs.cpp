#include <iostream>
#include <string>
#include <tuple>

namespace
{
template <typename... Ts> class Storage
{
  public:
    Storage(Ts &&...args) : _elements{args...}
    {
    }

    const std::tuple<Ts...> &Elements() const
    {
        return _elements;
    }

  private:
    std::tuple<Ts...> _elements;
};
template <typename... Ts> Storage(Ts &&...args) -> Storage<Ts...>;

template <typename... Ts> class Visitor : public Ts...
{
  public:
    using Ts::operator()...;
};
} // namespace

int main()
{
    auto myStorage = Storage{1, 2.2, std::string{"hello"}};
    const auto &elements{myStorage.Elements()};
    std::cout << "Storage: int = " << std::get<int>(elements) << ", double = " << std::get<double>(elements)
              << ", stirng = " << std::get<std::string>(elements) << "\n";

    std::cout << "\n\n";

    Visitor printVisitor{
        [](int i) { std::cout << "int: " << i << "\n"; },
        [](double d) { std::cout << "double: " << d << "\n"; },
        [](std::string s) { std::cout << "str: " << s << "\n"; },
    };
    printVisitor(10);
    printVisitor(20.22);
    printVisitor(std::string{"Sleek visitor implementation"});
}
