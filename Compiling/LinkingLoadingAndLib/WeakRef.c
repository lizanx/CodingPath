#include <stdio.h>

__attribute__((weakref)) void foo();

int main()
{
    if (foo)
    {
        printf("foo defined, call it.\n");
        foo();
    }
    else
    {
        printf("foo not defined, skip it.\n");
    }

    return 0;
}
