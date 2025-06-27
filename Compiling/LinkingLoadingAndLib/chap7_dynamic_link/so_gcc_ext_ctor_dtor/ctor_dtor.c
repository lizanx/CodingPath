#include <stdio.h>

// gcc -shared -fPIC -o libso_ext.so ctor_dtor.c

void __attribute__((constructor)) init_function()
{
    printf("This is so init function which should be called when loading.\n");
}

void __attribute__((destructor)) exit_function()
{
    printf("This is so exit function which should be called when exiting.\n");
}

void func()
{
    printf("Calling func in so lib..\n");
}
