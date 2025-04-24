#include "include/car.hpp"
#include <iostream>

static const std::vector<Car> AVAILABLE_CARS{
    {"BMW", "525", 31.5},
    {"BYD", "Dolphin", 10.23},
    {"Volvo", "S90", 32.3}};

const std::vector<Car> &GetAvailableCars()
{
    return AVAILABLE_CARS;
}

void PrintCar(const Car &car)
{
    std::cout << "Car[" << car.Brand << "-" << car.Model << ", $" << car.Price << "]\n";
}
