#include <chrono>
#include <future>
#include <iostream>
#include <thread>

namespace
{
    int Compute(int x, int y)
    {
        std::this_thread::sleep_for(std::chrono::seconds{3});
        return (x + y) * (x - y);
    }

    void ProduceResult(std::promise<int> pm, int x, int y)
    {
        pm.set_value(Compute(x, y));
    }
}

int main()
{
    // Future & Promise
    std::promise<int> pm{};
    std::future<int> ft1 = pm.get_future();
    std::thread t1{ProduceResult, std::move(pm), 10, 5};
    t1.join();
    std::cout << "Get t1 result: " << ft1.get() << "\n";

    // Packaged task
    std::packaged_task<int(int, int)> task = std::packaged_task{Compute};
    auto ft2 = task.get_future();
    task(7, 3);
    std::cout << "Get packaged task result: " << ft2.get() << "\n";

    // std::async
    std::future<int> ft3 = std::async(std::launch::async, Compute, 11, 2);
    std::cout << "Get async result: " << ft3.get() << "\n";
}
