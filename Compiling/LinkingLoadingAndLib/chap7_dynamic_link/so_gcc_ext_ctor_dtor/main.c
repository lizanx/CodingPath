#include <stdio.h>

// gcc -o main -L. -lso_ext  -Wl,-rpath,$(pwd) main.c

extern void func();

int main(int argc, char *argv[])
{
    printf("Running main..\n");
    func();

    return 0;
}
