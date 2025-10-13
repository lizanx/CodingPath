#include <iostream>

int main(int argc, char *argv[])
{
    constexpr double d = 1234.56789;
    std::cout << std::format("-{:12}-{:12.8f}-{:30.20e}-\n", d, d, d);
}
