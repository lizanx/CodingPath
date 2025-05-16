#pragma once

typedef struct car
{
    char brand[128];
    char model[128];
} car;

char *describe(const car *car);
