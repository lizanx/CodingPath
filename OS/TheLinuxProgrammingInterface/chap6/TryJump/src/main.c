#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "tlpi_hdr.h"

static jmp_buf jbuf;

static void f2()
{
    printf("Currently in f2\n");
    longjmp(jbuf, 2);
}

static void f1(bool jumpNow)
{
    printf("Currently in f1\n");
    if (jumpNow)
        longjmp(jbuf, 1);
    else
        f2();
}

static void SimpleJump(bool jumpNow)
{
    printf("%s\n", __func__);
    switch (setjmp(jbuf))
    {
    case 0:
        printf("Call f1, jumpNow = %d\n", jumpNow);
        f1(jumpNow);
        break;
    case 1:
        printf("Jumped from f1.\n");
        break;
    case 2:
        printf("Jumped from f2.\n");
        break;
    default:
        break;
    }
}

static jmp_buf jbuf2;

static void g(int a, int b, int c)
{
    printf("In g, a = %d, b = %d, c = %d\n", a, b, c);
    longjmp(jbuf2, 1);
}

static void OptimizationCausesError()
{
    int a = 1;          // Value of this auto var after jumping back from g depends on optimization policy.
    register int b = 2; // This register auto var won't be correctly set even without optimization after jumping back from g, because it's(usually) allocated in a register.
    volatile int c = 3; // This volatile auto var will be correctly set even with optimization after jumping back from g.

    printf("Initially, a = %d, b = %d, c = %d\n", a, b, c);
    if (setjmp(jbuf2) == 0)
    {
        a = 4;
        b = 5;
        c = 6;
        printf("Calling g...\n");
        g(a, b, c);
    }
    else
    {
        printf("Jumped back from g: a = %d, b = %d, c = %d\n", a, b, c);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        SimpleJump(false);
    else
        SimpleJump(true);

    printf("\n\nThe following demo shows that compiler optimization might cause variable value loss with setjmp/longjmp.\n\n");

    OptimizationCausesError();

    return 0;
}
