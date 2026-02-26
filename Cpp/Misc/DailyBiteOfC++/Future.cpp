#include <chrono>
#include <future>
#include <print>
#include <stdexcept>
#include <string>
#include <thread>

int main()
{
    {
        std::promise<std::string> promise{};
        auto fut = promise.get_future();
        std::jthread t{[promise = std::move(promise)] mutable
                       {
                           std::this_thread::sleep_for(std::chrono::seconds{2});
                           promise.set_value("hello world");
                       }};
        std::println("Result: {}", fut.get());
    }

    {
        std::promise<std::string> promise{};
        auto fut = promise.get_future();
        std::jthread t{[promise = std::move(promise)] mutable
                       {
                           try
                           {
                               throw std::runtime_error{"Some error."};
                               promise.set_value("hello world");
                           }
                           catch (...)
                           {
                               promise.set_exception(std::current_exception());
                           }
                       }};
        try
        {
            std::println("Result: {}", fut.get());
        }
        catch (const std::exception &e)
        {
            std::println("Error: {}", e.what());
        }
    }

    {
        std::promise<std::string> promise{};
        auto fut = promise.get_future();
        std::jthread t{[promise = std::move(promise)] mutable
                       {
                           std::this_thread::sleep_for(std::chrono::seconds{2});
                           promise.set_value("hello world");
                       }};
        if (auto status = fut.wait_for(std::chrono::seconds{1}); status == std::future_status::ready)
            std::println("Result: {}", fut.get());
        else if (status == std::future_status::timeout)
            std::println("Timeout!");
        else
            std::println("Error(unknown)");
    }

    return 0;
}
