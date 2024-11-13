#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>

int main()
{
    int i = 5, j = 9;
    double d1 = 1.3, d2 = 2.6;

    std::cout << std::fabs(-i) << " " << std::exp2(i) << " " << std::sqrt(j) << "\n"
              << std::floor(d1) << " " << std::ceil(d1) << "\n"
              << std::round(d1) << " " << std::round(d2) << "\n"
              << std::numeric_limits<int>::max() << "\n"
              << std::numeric_limits<double>::min() << "\n";
}