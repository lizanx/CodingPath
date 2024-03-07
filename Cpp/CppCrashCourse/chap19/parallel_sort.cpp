#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

struct Stopwatch
{
    explicit Stopwatch(chrono::nanoseconds &result)
        : result{result}, start{chrono::high_resolution_clock::now()} {}
    ~Stopwatch()
    {
        result = chrono::high_resolution_clock::now() - start;
    }

private:
    chrono::nanoseconds &result;
    const chrono::time_point<chrono::high_resolution_clock> start;
};

vector<int> make_random_vector(void)
{
    vector<int> v(100'000'000);
    iota(v.begin(), v.end(), 0);
    mt19937_64 urng{ 121216 };
    shuffle(v.begin(), v.end(), urng);
    return v;
}

int main(void)
{
    cout << "Constructing vectors..." << endl;
    auto nums1 = make_random_vector();
    auto nums2 = nums1;

    chrono::nanoseconds time_to_sort{};
    cout << " " << nums1.size() << " elements." << endl;

    cout << "Sorting with execution::seq..." << endl;
    {
        Stopwatch sw{ time_to_sort };
        sort(execution::seq, nums1.begin(), nums1.end());
    }
    cout << "Took " << (time_to_sort.count() / 1.0E9) << " sec." << endl;

    cout << "Sorting with execution::par..." << endl;
    {
        Stopwatch sw{ time_to_sort };
        sort(execution::par, nums2.begin(), nums2.end());
    }
    cout << "Took " << (time_to_sort.count() / 1.0E9) << " sec." << endl;
}