#include <print>
#include <ranges>
#include <map>

int main()
{
    std::map<std::string, int> nums{
        {"One", 1},
        {"Two", 2},
        {"Three", 3}};

    for (const std::string &key : nums | std::views::keys)
        std::println("Key: {}", key);

    for (int n : nums | std::views::values)
        std::println("Value: {}", n);

    return 0;
}
