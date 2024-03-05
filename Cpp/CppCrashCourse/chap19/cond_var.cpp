#include <string>
#include <future>
#include <iostream>
#include <mutex>
#include <condition_variable>

int main(int argc, char *argv[])
{
    int counter{};
    const size_t iterations{ 1000 };
    std::mutex m{};
    std::condition_variable cv{};

    const auto inc = [&]() {
        for (size_t i{}; i < iterations; i++)
        {
            std::unique_lock lock{ m };
            cv.wait(lock, [&]() { return counter < 0; });
            std::cout << "Wakeup\n";
            counter++;
        }
    };
    const auto dec = [&]() {
        for (size_t i{}; i < iterations; i++)
        {
            std::unique_lock lock{ m };
            counter--;
            std::cout << "Notify\n";
            cv.notify_all();
        }
    };
    auto incResult = std::async(std::launch::async, inc);
    auto decResult = std::async(std::launch::async, dec);
    incResult.wait();
    decResult.wait();
    
    std::cout << counter << std::endl;
}