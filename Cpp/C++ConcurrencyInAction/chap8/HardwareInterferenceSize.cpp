#include <iostream>
#include <new>

int main(int argc, char *argv[])
{
    std::cout << "hardware_destructive_interference_size: " << std::hardware_destructive_interference_size << '\n'
              << "hardware_constructive_interference_size: " << std::hardware_constructive_interference_size << '\n';
}
