#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

namespace
{
    void WorkerPrintEach2SecondFor5Times()
    {
        for (int i{}; i < 5; ++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds{2});
            std::cout << "WorkerPrintEach2SecondFor5Times" << '\n';
        }
    }

    void DemoNoJoinOrDetachCauseTerminate()
    {
        std::cout << "Start DemoNoJoinOrDetachCauseTerminate" << '\n';
        std::thread t{WorkerPrintEach2SecondFor5Times};
        std::this_thread::sleep_for(std::chrono::seconds{12});
        std::cout << "End DemoNoJoinOrDetachCauseTerminate" << '\n';
        // Here, upon exit, "t" is destructed.
        // Since nor "join()" nor "detach()" is called, "std::terminate()" is called here.
    }

    void DemoJoin()
    {
        class ThreadJoinGuard
        {
        public:
            ThreadJoinGuard(std::thread &thread) : _thread{thread} {}
            ~ThreadJoinGuard()
            {
                if (_thread.joinable())
                    _thread.join();
            }
            ThreadJoinGuard(const ThreadJoinGuard &) = delete;
            ThreadJoinGuard &operator=(const ThreadJoinGuard &) = delete;

        private:
            std::thread &_thread;
        };

        std::cout << "Start DemoJoin" << '\n';
        std::thread t{WorkerPrintEach2SecondFor5Times};
        ThreadJoinGuard guard{t};
        {
            // Do some work and throw.
            std::this_thread::sleep_for(std::chrono::seconds{6});
            std::cout << "Throwing...\n";
            throw std::runtime_error{"Exception from DemoJoin"};
        }
        std::cout << "End DemoJoin" << '\n';
    }

    void DemoDetach()
    {
        std::cout << "Start DemoDetach" << '\n';
        std::thread t{WorkerPrintEach2SecondFor5Times};
        t.detach();
        std::cout << "End DemoDetach" << '\n';
    }
}

int main(int argc, char *argv[])
{
    DemoNoJoinOrDetachCauseTerminate();

    // try
    // {
    //     DemoJoin();
    // }
    // catch (const std::runtime_error &e)
    // {
    //     std::cout << "Exception caught: " << e.what() << '\n';
    // }

    // DemoDetach();
    // std::this_thread::sleep_for(std::chrono::seconds{5}); // Exit before the detached thread finishes, process ends, detached thread not executing any more.
    // std::this_thread::sleep_for(std::chrono::seconds{12}); // Exit after the detached thread finishes.

    std::cout << "Exit main" << std::endl;
}
