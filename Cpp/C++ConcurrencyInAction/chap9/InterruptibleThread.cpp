#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <syncstream>
#include <thread>

namespace
{
    int RandInt(int low, int high)
    {
        static std::random_device rd{};
        static std::mt19937 engine{rd()};
        std::uniform_int_distribution distribution{low, high};
        return distribution(engine);
    }

    void ThreadFn(std::stop_token stopToken, std::osyncstream &oss, unsigned tid)
    {
        oss << "Thread[" << tid << "] started\n";
        std::ofstream ofs{std::format("Thread-{}.txt", tid)};
        for (;;)
        {
            if (stopToken.stop_requested())
            {
                oss << "Thread[" << tid << "] stopped!!!\n";
                break;
            }
            int n = RandInt(1, 100);
            ofs << n << std::endl;
            if (n % 23 == 0)
            {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds{100});
        }
    }
}

int main(int argc, char *argv[])
{
    constexpr unsigned THREAD_CNT{10};
    std::vector<std::jthread> ts{};
    ts.reserve(THREAD_CNT);
    std::osyncstream oss{std::cout};
    for (unsigned i{}; i < THREAD_CNT; ++i)
    {
        ts.push_back(std::jthread{ThreadFn, std::ref(oss), i});
    }
    std::this_thread::sleep_for(std::chrono::milliseconds{205});
    for (unsigned i{}; i < THREAD_CNT; i += 3)
    {
        ts[i].request_stop();
    }
    for (auto &t : ts)
        t.join();
    oss << "## Exit main ##\n";

    return EXIT_SUCCESS;
}
