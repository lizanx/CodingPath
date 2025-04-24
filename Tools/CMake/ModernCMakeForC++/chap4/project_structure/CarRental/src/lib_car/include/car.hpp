#ifndef _CAR_HEADER_
#define _CAR_HEADER_

#include <string>
#include <vector>

struct Car
{
    std::string Brand;
    std::string Model;
    double Price;
};

const std::vector<Car> &GetAvailableCars();

void PrintCar(const Car &car);

#endif /* _CAR_HEADER_ */
