#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void f1()
{
    std::cout << "f1(), thread id = " << std::this_thread::get_id() << "\n";
}

void f2(size_t index)
{
    std::cout << "f2(), thread id = " << std::this_thread::get_id() << ", "
              << "index = " << index << "\n";
}

void f3(int &value)
{
    ++value;
}

int main()
{
    using namespace std::chrono_literals;

    std::cout << "Thread id: " << std::this_thread::get_id() << "\n";
    std::cout << "Max supported paralellism: " << std::thread::hardware_concurrency() << "\n";
    std::this_thread::sleep_for(3s);

    std::thread t1(f1);
    t1.join();

    std::vector<std::thread> threadVec{};
    for (size_t i{}; i < 10; ++i)
    {
        threadVec.push_back(std::thread(f2, i));
    }
    for (auto &t : threadVec)
    {
        t.join();
    }
    threadVec.clear();

    for (size_t i{}; i < 10; ++i)
    {
        threadVec.push_back(std::thread([i]()
                                        { std::cout << "Lambda thread " << i << "\n"; }));
    }
    for (auto &t : threadVec)
    {
        t.join();
    }
    threadVec.clear();

    int value{};
    for (size_t i{}; i < 10000; ++i)
    {
        threadVec.push_back(std::thread(f3, std::ref(value))); // Here we must use std::ref for reference passing
    }
    for (auto &t : threadVec)
    {
        t.join();
    }
    std::cout << "After all threads calculation, value = " << value << "\n";
}
