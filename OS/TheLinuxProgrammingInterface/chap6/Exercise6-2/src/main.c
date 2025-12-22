#include <stdio.h>
#include <setjmp.h>
#include "tlpi_hdr.h"

static jmp_buf jb;

static void f()
{
    int a = 111, b = 222;
    if (setjmp(jb) == 0)
    {
        printf("Jump entry set.\n");
    }
    else
    {
        printf("Jumped back! a = %d, b = %d\n", a, b); // Value of a/b are undefined since jump happens outside function call chain below 'f'.
    }
}

static void g()
{
    printf("In g..\n");
    longjmp(jb, 1);
}

static void h()
{
    printf("This is some random function to mess up call stack..\n");
    int a = 1;
    int b = 2;
    printf("a + b = %d\n", a + b);
}

int main(int argc, char *argv[])
{
    printf("[main] Call f()\n");
    f();

    printf("[main] Call h()\n");
    h();

    printf("[main] Call g()\n");
    g();

    printf("[main] done.\n");
    return 0;
}
