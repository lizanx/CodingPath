#include <string>

struct House
{
    House() : Location{ "Unknown" }, Price { 0 } {}
    House(const char* const location, double price) : Location{ location }, Price { price } {}

    std::string Location;
    double Price;
};
