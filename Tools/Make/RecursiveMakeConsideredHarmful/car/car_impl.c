#include "car_impl.h"
#include <stdlib.h>

char *describe_impl(const car *car)
{
    if (!car)
        return NULL;

    int brand_len = strlen(car->brand);
    int model_len = strlen(car->model);
    int desc_len = brand_len + model_len + 1;
    char *description = malloc(sizeof(char) * (desc_len));
    if (!description)
        return NULL;
    strncpy(description, car->brand, brand_len);
    strncpy(description + brand_len, car->model, model_len);
    description[desc_len - 1] = '\0';
    return description;
}
