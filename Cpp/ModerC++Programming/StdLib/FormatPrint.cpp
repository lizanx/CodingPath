#include <iostream>
#include <fmt/core.h>

int main()
{
    int i = 57;
    double d = 3.14;

    std::cout << fmt::format("{}\n", i)
              << fmt::format("{:b}\n", i)
              << fmt::format("{1:<5}+{0:>3} = {2}\n", i, d, i + d);
}
