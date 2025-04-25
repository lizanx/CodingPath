#include "configure.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
#ifdef DEF_VAR_1
    std::cout << "VAR_1 defined.\n";
#else
    std::cout << "VAR_1 not defined!\n";
#endif

#ifdef DEF_VAR_2
    std::cout << "VAR_2 defined: " << DEF_VAR_2 << "\n";
#else
    std::cout << "VAR_2 not defined!\n";
#endif

#ifdef DEF_VAR_3
    std::cout << "VAR_3 defined: " << DEF_VAR_3 << "\n";
#else
    std::cout << "VAR_3 not defined!\n";
#endif

#ifdef DEF_VAR_4
    std::cout << "VAR_4 defined: " << DEF_VAR_4 << "\n";
#else
    std::cout << "VAR_4 not defined!\n";
#endif

    return 0;
}
