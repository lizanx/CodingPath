#include <algorithm>
#include <chrono>
#include <print>
#include <random>
#include <thread>
#include <vector>

int main()
{
    using std::vector;
    vector<int> v1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto v2 = v1;
    std::println("original:");
    std::print("\t");
    for (int n : v1)
        std::print("{} ", n);
    std::println();

    std::shuffle(v1.begin(), v1.end(), std::default_random_engine{static_cast<unsigned long long>(std::chrono::system_clock::now().time_since_epoch().count())});
    std::println("v1:");
    std::print("\t");
    for (int n : v1)
        std::print("{} ", n);
    std::println();

    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // For different random engine seed.
    std::ranges::shuffle(v2, std::default_random_engine{static_cast<unsigned long long>(std::chrono::system_clock::now().time_since_epoch().count())});
    std::println("v2:");
    std::print("\t");
    for (int n : v2)
        std::print("{} ", n);
    std::println();

    return 0;
}
