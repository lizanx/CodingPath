#include <chrono>
#include <iostream>
#include <latch>
#include <string>
#include <thread>

namespace
{
    struct Job
    {
        std::string Name{};
        std::thread Thread{};
        std::string Result{};
    };

    void ProcessJob(Job &job, std::latch &doneLatch, std::latch &cleanupLatch, int sleepSeconds)
    {
        std::cout << "Processing Job " << job.Name << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds{sleepSeconds});
        job.Result = job.Name + " Finished";
        doneLatch.count_down();
        cleanupLatch.wait();
        std::cout << "Cleaning Job " << job.Name << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds{sleepSeconds});
        job.Result = job.Name + " Cleaned";
    }
}

int main(int argc, char *argv[])
{
    Job jobs[]{
        {"Study"},
        {"Chores"},
        {"Exercises"},
        {"Cooking"}};
    std::latch processJobLatch{std::size(jobs)};
    std::latch cleanJobLatch{1};

    std::cout << "===== Processing Jobs =====\n";
    for (std::size_t i{}; i < std::size(jobs); ++i)
    {
        jobs[i].Thread = std::thread{ProcessJob, std::ref(jobs[i]), std::ref(processJobLatch), std::ref(cleanJobLatch), i};
    }
    processJobLatch.wait();
    for (Job &job : jobs)
        std::cout << "\t" << job.Result << "\n";

    std::cout << "===== Cleaning Jobs =====\n";
    cleanJobLatch.count_down();
    for (Job &job : jobs)
        job.Thread.join();
    for (Job &job : jobs)
        std::cout << "\t" << job.Result << "\n";
}
