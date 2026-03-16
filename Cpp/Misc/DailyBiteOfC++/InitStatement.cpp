#include <optional>
#include <print>
#include <string>

namespace
{
    std::optional<int> Foo()
    {
        return 10;
    }

    int Bar()
    {
        return 20;
    }
}

int main()
{
    if (auto result = Foo(); result.has_value())
    {
        std::println("Result: {}", *result);
    }

    switch (auto val = Bar(); val)
    {
    case 10:
        std::println("case 10");
        break;
    case 20:
        std::println("case 20");
        break;
    default:
        std::println("Unknown case");
        break;
    }

    std::print("str: ");
    for (std::string str = std::to_string(Bar()); auto c : str)
    {
        std::print("[{}] ", c);
    }
    std::println();

    return 0;
}
