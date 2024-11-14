#include <iostream>
#include <optional>

static std::optional<char> FindChar(const char *str, char c)
{
    if (str == nullptr)
        return std::nullopt;

    while (*str)
    {
        if (*str == c)
            return c;
        ++str;
    }

    return {};
}

int main()
{
    const char *const str = "Hello, world!";
    auto a = FindChar(str, 'a');
    std::cout << "FindChar(a): " << std::boolalpha
              << a.has_value() << " "
              << a.value_or('#') << "\n";
    auto e = FindChar(str, 'e');
    std::cout << "FindChar(e): " << std::boolalpha
              << e.has_value() << " "
              << e.value() << " "
              << *e << " "
              << e.value_or('#') << "\n";
}