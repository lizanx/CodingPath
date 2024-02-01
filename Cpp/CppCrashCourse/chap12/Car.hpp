#include <string>

struct Car
{
    Car() : Brand{ "Unknown" }, Price { 0 } {}
    Car(const char* const brand, double price) : Brand{ brand }, Price { price } {}

    std::string Brand;
    double Price;
};
