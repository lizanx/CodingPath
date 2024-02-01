#include <optional>
#include <iostream>

#include "Person.hpp"

int main(int argc, char *argv[])
{
    std::optional<Person> op1{};
    std::optional<Person> op2{};
    op2.emplace("Claire", 22);
    std::optional<Person> op3{ Person("John", 25) };

    if (op1.has_value())
    {
        std::cout << "--- Optional 1 ---\n";
    }
    if (op1 == std::nullopt)
    {
        std::cout << "--- Optional 1 is nullopt ---\n";
    }
    if (op2)
    {
        std::cout << "--- Optional 2 ---\n";
        std::cout << "Name: " << op2->Name << "\nAge: " << op2.value().Age << std::endl;
    }
    if (op3)
    {
        std::cout << "--- Optional 3 ---\n";
        std::cout << "Name: " << (*op3).Name << "\nAge: " << op3->Age << std::endl;
    }

}