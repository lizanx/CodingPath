#include <iostream>

extern int GetNumber();

int main()
{
    std::cout << "Number: " << GetNumber() << "\n";
}
