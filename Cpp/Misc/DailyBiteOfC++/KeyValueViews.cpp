#include <map>
#include <print>
#include <ranges>
#include <unordered_map>

int main()
{
    std::unordered_map<std::string, int> data{
        {"One", 1},
        {"Two", 2},
        {"Three", 3}};

    for (const auto &key : data | std::views::keys)
    {
        std::println("Key: {}", key);
    }

    for (const auto &value : data | std::views::values)
    {
        std::println("Value: {}", value);
    }

    return 0;
}
