#include <iostream>
#include <random>
#include <array>
#include <functional>
#include <string>

int main()
{
    std::array<int, 5> arr{};
    auto randomGenerator = std::bind(std::uniform_int_distribution{0, 4}, std::default_random_engine{});
    for (size_t i{}; i < 200; i++)
    {
        ++arr[randomGenerator()];
    }

    for (size_t i{}; i < arr.size(); i++)
    {
        std::cout << i << "\t" << std::string(arr[i], '*') << "\n";
    }
}
