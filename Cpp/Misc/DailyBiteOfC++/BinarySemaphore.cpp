#include <chrono>
#include <condition_variable>
#include <print>
#include <semaphore>
#include <thread>

namespace
{
    void Demo_BinarySemaphore()
    {
        std::binary_semaphore sem{0};

        auto t = std::jthread{[&sem]()
                              {
                                  std::println("Waiting for sem...");
                                  sem.acquire();
                                  std::println("Semaphore acquired!");
                                  std::println("Done");
                              }};

        std::println("Wait for a while before signaling sem..");
        std::this_thread::sleep_for(std::chrono::seconds{2});

        std::println("Signal sem.");
        sem.release();
    }

    void Demo_MutexCondVar()
    {
        std::mutex mutex{};
        std::condition_variable cv{};
        bool ready{};

        auto t = std::jthread{[&mutex, &cv, &ready]()
                              {
                                  std::println("Wait for cond_var...");
                                  std::unique_lock lck{mutex};
                                  cv.wait(lck, [&ready]()
                                          { return ready; });
                                  std::println("Ready!");
                              }};
        {
            std::unique_lock lck{mutex};
            std::println("Wait for a while before setting ready..");
            std::this_thread::sleep_for(std::chrono::seconds{2});
            ready = true;
        }
        std::println("Notifying conditional var.");
        cv.notify_one();
    }
}

int main()
{
    std::println("Enter main");

    std::println("=== Demo_BinarySemaphore ===");
    Demo_BinarySemaphore();

    std::this_thread::sleep_for(std::chrono::seconds{5});

    std::println("=== Demo_MutexCondVar ===");
    Demo_MutexCondVar();

    return 0;
}
