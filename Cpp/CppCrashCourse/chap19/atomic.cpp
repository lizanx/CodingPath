#include <string>
#include <future>
#include <iostream>
#include <atomic>

int main(int argc, char *argv[])
{
    std::atomic_int counter{};
    const size_t iterations{ 1'000'000 };

    const auto inc = [&]() {
        for (size_t i{}; i < iterations; i++)
        {
            counter++;
        }
    };
    const auto dec = [&]() {
        for (size_t i{}; i < iterations; i++)
        {
            counter--;
        }
    };
    auto incResult = std::async(std::launch::async, inc);
    auto decResult = std::async(std::launch::async, dec);
    incResult.wait();
    decResult.wait();
    
    std::cout << counter << std::endl;
}