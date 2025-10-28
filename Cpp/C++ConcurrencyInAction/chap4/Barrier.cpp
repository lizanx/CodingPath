#include <barrier>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>

namespace
{
    int GetRandomInt(int start, int end)
    {
        static std::random_device rd{};
        static std::mt19937 engine{rd()};
        static std::mutex randMutex{};

        std::lock_guard lck{randMutex};
        std::uniform_int_distribution distribution{start, end};
        return distribution(engine);
    }

    struct Task
    {
        std::string Name{};
        int Result{};
        static int Round;
    };

    int Task::Round{};
}

int main(int argc, char *argv[])
{
    std::vector<Task> tasks{};
    for (int i{}; i < 5; ++i)
        tasks.emplace_back(std::format("Task-{}", i), 0);
    auto completionStep = [&tasks]()
    {
        std::cout << "===== Round " << Task::Round << " Finished =====\n";
        ++Task::Round;
        for (Task &task : tasks)
            std::cout << "-> Task[" << task.Name << "].Result = " << task.Result << "\n";
    };
    std::barrier barrier{std::ssize(tasks), completionStep};
    auto workerFn = [&barrier](Task &task, int incStepMax, int threshold)
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds{GetRandomInt(1, 3)});
            task.Result += GetRandomInt(0, incStepMax);
            if (task.Result >= threshold)
            {
                barrier.arrive_and_drop();
                break;
            }
            else
            {
                barrier.arrive_and_wait();
            }
        }
    };
    std::vector<std::thread> threads(tasks.size());
    for (int i{}; i < threads.size(); ++i)
    {
        threads[i] = std::thread{workerFn, std::ref(tasks[i]), 10, 100};
    }
    for (auto &t : threads)
        t.join();
}
