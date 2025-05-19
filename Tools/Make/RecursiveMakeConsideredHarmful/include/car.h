#pragma once

typedef struct car
{
    char brand[128];
    char model[126];
} car;

char *describe(const car *car);
