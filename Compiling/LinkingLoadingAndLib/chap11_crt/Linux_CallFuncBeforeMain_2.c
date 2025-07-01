#include <stdio.h>

void __attribute__((constructor)) my_init()
{
    printf("Hello ");
}

// typedef void (*ctor)(void);

// ctor __attribute__((section(".ctors"))) my_init_p = &my_init;

int main()
{
    printf("World\n");

    return 0;
}
