#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <csignal>

static std::atomic_bool interrupted{};

extern "C" void handler(int signal)
{
    std::cout << "Handler invoked with signal " << signal << "\n";
    interrupted = true;
}

int main()
{
    std::signal(SIGINT, handler);

    using namespace std::literals::chrono_literals;
    while (!interrupted)
    {
        std::cout << "Waiting..." << std::endl;
        std::this_thread::sleep_for(1s);
    }
    std::cout << "Interrupted!\n";
}
