#include <iostream>
#include <variant>

#include "Person.hpp"
#include "Car.hpp"
#include "House.hpp"

int main(int argc, char *argv[])
{
    std::variant<Person, Car, House> v{};
    std::cout << "index: " << v.index() << std::endl;

    v = Car("VW", 15'000);
    std::cout << "index: " << v.index() << std::endl;
    if (std::holds_alternative<Car>(v))
        std::cout << "Car in variant: " << std::get<Car>(v).Brand << ", " << std::get<1>(v).Price << std::endl;
    else
        std::cout << "Car not in variant!" << std::endl;

    v.emplace<House>("Paris", 800'000);
    std::cout << "index: " << v.index() << std::endl;
    try
    {
        const auto& house = std::get<House>(v);
        std::cout << "House in variant: " << house.Location << ", of price " << house.Price << std::endl;
    }
    catch(const std::bad_variant_access& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
