#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

namespace
{
    std::atomic_bool g_ready{};
    std::mutex g_mutex{};
    std::condition_variable_any cv{};

    void worker(std::stop_token stoken)
    {
        std::stop_callback cb{stoken, []()
                              { std::cout << "Stop callback triggered\n"; }};

        std::unique_lock lck{g_mutex};
        cv.wait_for(lck, stoken, std::chrono::seconds{5}, []()
                    { return g_ready.load(std::memory_order_acquire); });
        if (stoken.stop_requested())
        {
            std::cout << "The worker was cancelled\n";
        }
        else if (g_ready.load(std::memory_order_acquire))
        {
            std::cout << "Data is ready!\n";
        }
        else
        {
            std::cout << "Timeout!\n";
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: <program> [1|2|3]\n";
        exit(EXIT_FAILURE);
    }

    long option = std::strtol(argv[1], nullptr, 10);

    std::jthread t{worker};

    switch (option)
    {
    case 1L:
        // 1: stop
        t.request_stop();
        break;
    case 2L:
        // 2: ready
        g_ready.store(true, std::memory_order_release);
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds{1}); // sleep to wait for join of 't', otherwise the main thread may end earlier than jthread, thus calling "request_stop" on 't'.
        break;
    case 3L:
        // 3: timeout
        std::this_thread::sleep_for(std::chrono::seconds{6});
        break;
    default:
        std::cerr << "Unknown option " << option << "\n";
        exit(EXIT_FAILURE);
        break;
    }

    return EXIT_SUCCESS;
}
