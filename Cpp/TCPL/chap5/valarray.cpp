#include <iostream>
#include <valarray>

int main()
{
    std::valarray va{1, 2, 3, 4, 5};

    auto va2 = va + 1;
    std::cout << "va + 1:\n";
    for (size_t i{}; i < va.size(); i++)
    {
        std::cout << va2[i] << '\t';
    }
    std::cout << "\n\n";
    
    auto va3 = va * 2;
    std::cout << "va * 2:\n";
    for (size_t i{}; i < va.size(); i++)
    {
        std::cout << va3[i] << '\t';
    }
    std::cout << "\n\n";
    
    auto va4 = va % 3;
    std::cout << "va % 3:\n";
    for (size_t i{}; i < va.size(); i++)
    {
        std::cout << va4[i] << '\t';
    }
    std::cout << "\n\n";
}