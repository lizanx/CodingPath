#include <iostream>
#include <any>

#include "Person.hpp"
#include "Car.hpp"
#include "House.hpp"

int main(int argc, char *argv[])
{
    std::any a{};
    std::cout << "any has " << (a.has_value() ? "value" : "no value") << std::endl;
    a.emplace<Person>("Rob", 54);
    const auto& p = std::any_cast<Person>(a);
    std::cout << "In a: Person " << p.Name << ", " << p.Age << std::endl;
    a.reset();
    if (a.has_value())
        std::cout << "has value\n";
    else
        std::cout << "has no value\n";
    a.emplace<House>("Seattle", 200'000);
    std::cout << "In a: House in " << std::any_cast<House>(a).Location << std::endl;
}