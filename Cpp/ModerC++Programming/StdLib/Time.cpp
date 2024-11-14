#include <chrono>
#include <iostream>
#include <thread>
#include <time.h>
#include <sys/time.h>

// System time
static void MeasureTime1()
{
    std::cout << "--- 1 ---\n";

    timeval start, end;
    ::gettimeofday(&start, NULL);
    std::this_thread::sleep_for(std::chrono::milliseconds{2500});
    ::gettimeofday(&end, NULL);

    long startTime = start.tv_sec * 1'000'000 + start.tv_usec;
    long endTime = end.tv_sec * 1'000'000 + end.tv_usec;

    std::cout << "Elapsed: " << (endTime - startTime) << "us\n";
}

// System time
// System clock will be affected by time zone.
static void MeasureTime2()
{
    std::cout << "--- 2 ---\n";

    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds{2500});
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> timeElapsed = end - start;
    std::cout << "Elapsed: "
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us\n";
}

// System time
// Steady clock won't be affected by time zone.
static void MeasureTime3()
{
    std::cout << "--- 3 ---\n";

    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds{2500});
    auto end = std::chrono::steady_clock::now();

    auto timeElapsed = end - start;
    std::cout << "Elapsed: "
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us\n";
}

// User time
static void MeasureTime4()
{
    std::cout << "--- 4 ---\n";

    clock_t start = std::clock();
    std::this_thread::sleep_for(std::chrono::milliseconds{2500});
    clock_t end = std::clock();

    std::cout << "Elapsed: "
              << (static_cast<double>(end - start) * 1'000'000 / CLOCKS_PER_SEC)
              << "us\n";
}

int main()
{
    MeasureTime1();
    MeasureTime2();
    MeasureTime3();
    MeasureTime4();
}
