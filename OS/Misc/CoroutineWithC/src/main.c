#include "coroutine.h"
#include <stdio.h>
#include <stdint.h>

#define STACK_SIZE 1024 * 1024

void *number(void *param)
{
    intptr_t i = (intptr_t)param;
    co_yield(NULL, NULL);
    while (1)
    {
        co_yield((void *)i, NULL);
        ++i;
    }
}

int main()
{
    struct coroutine *num = co_new(number, STACK_SIZE);
    co_resume(num, (void *)0, NULL);
    for (int i = 0; i < 10; ++i)
    {
        intptr_t n;
        co_resume(num, NULL, (void **)&n);
        printf("%ld ", n);
    }
    co_free(num);
    return 0;
}
