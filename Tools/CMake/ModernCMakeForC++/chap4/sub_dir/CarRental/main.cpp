#include "car.hpp"

int main(int argc, char *argv[])
{
    for (const auto &car : GetAvailableCars())
    {
        PrintCar(car);
    }
}
