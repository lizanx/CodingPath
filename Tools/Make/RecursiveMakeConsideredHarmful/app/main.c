#include "car.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char argv[])
{
    car han;
    strncpy(han.brand, "BYD", sizeof(han.brand));
    strncpy(han.brand, "Dynasty-HAN", sizeof(han.model));
    char *han_description = describe(&han);
    if (!han_description)
    {
        printf("Failed to get description!");
    }
    else
    {
        printf("Car: %s\n", han_description);
        free(han_description);
        han_description = NULL;
    }

    return 0;
}
