#include <iostream>
#include <tuple>

#include "Person.hpp"
#include "Car.hpp"
#include "House.hpp"

int main(int argc, char *argv[])
{
    std::tuple<Person, Car, House> t{
        Person("Ken", 42),
        Car("BMW", 50'000),
        House("New York", 300'000)
    };
    std::cout << "tuple size: " << std::tuple_size<decltype(t)>::value << std::endl;
    auto& [person, car, house] = t;
    std::cout << person.Name << " lives in " << house.Location <<
        ", and has a car of " << car.Brand << std::endl;
    std::cout << std::get<Person>(t).Name << " lives in " << std::get<2>(t).Location <<
        ", and has a car of " << std::get<Car>(t).Brand << std::endl;
}
