#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Hello!\n";
    for (size_t i{}; i < argc; ++i)
        std::cout << argv[i] << "\n";

    return EXIT_SUCCESS;
}
