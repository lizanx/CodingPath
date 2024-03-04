#include <string>
#include <future>
#include <mutex>
#include <iostream>
// #define CATCH_CONFIG_MAIN
// #include "../catch.hpp"

int main(int argc, char *argv[])
{
    int counter{};
    const size_t iterations{ 1'000'000 };
    std::mutex m{};

    const auto inc = [&]() {
        for (size_t i{}; i < iterations; i++)
        {
            std::lock_guard guard{ m };
            counter++;
        }
    };
    const auto dec = [&]() {
        for (size_t i{}; i < iterations; i++)
        {
            std::lock_guard guard{ m };
            counter--;
        }
    };
    auto incResult = std::async(std::launch::async, inc);
    auto decResult = std::async(std::launch::async, dec);
    incResult.wait();
    decResult.wait();
    
    std::cout << counter << std::endl;
}