#include <iostream>
#include <utility>
#include "Person.hpp"
#include "Car.hpp"

int main(int argc, char *argv[])
{
    std::pair<Person, Car> p1{};
    auto p2 = std::make_pair<Person, Car>(Person("Gavin", 27), Car("BYD", 233'000));

    std::cout << "--- Pair 1 ---\n";
    std::cout << p1.first.Name << " has a car of brand " << p1.second.Brand << std::endl;
    std::cout << "--- Pair 2 ---\n";
    std::cout << std::get<Person>(p2).Name << " has a car of brand " << std::get<1>(p2).Brand << std::endl;
}