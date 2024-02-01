#include <iostream>
#include <random>

int main(int argc, char *argv[])
{
    std::random_device rd{};

    for (int i = 0; i < 10; i++)
        std::cout << rd() << std::endl;
}