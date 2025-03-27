#include <stdio.h>
#include "point.h"

void print_point(const Point *p)
{
    if (p)
    {
        printf("Point[%d, %d]\n", p->x, p->y);
    }
}
