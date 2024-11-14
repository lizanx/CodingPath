#include <any>
#include <iostream>

int main()
{
    std::cout << std::boolalpha;
    std::any var;
    std::cout << var.has_value() << "\n";
    var = 1;
    std::cout << var.has_value() << " "
              << var.type().name() << " "
              << std::any_cast<int>(var) << "\n";
    var = 3.3;
    std::cout << var.has_value() << " "
              << var.type().name() << " "
              << std::any_cast<double>(var) << "\n";
    try
    {
        std::cout << std::any_cast<int>(var) << "\n";
    }
    catch (std::bad_any_cast &e)
    {
        std::cout << "Failed to cast var to type int: " << e.what() << "\n";
    }
    var.reset();
    std::cout << "After reset, var has value? " << var.has_value() << "\n";
}
