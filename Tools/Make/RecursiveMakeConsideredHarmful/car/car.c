#include "car.h"
#include "car_impl.h"

char *describe(const car *car)
{
    return describe_impl(car);
}
