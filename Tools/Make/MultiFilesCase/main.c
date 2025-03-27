#include "point.h"

int main()
{
    Point p = {
        .x = 3,
        .y = 4};

    print_point(&p);

    return 0;
}
