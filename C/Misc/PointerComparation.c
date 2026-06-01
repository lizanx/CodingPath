#include <stdio.h>

int main(void)
{
    int a, b;
    int *p = &a;
    int *q = &b + 1;
    printf("p -> %p, q -> %p, equal -> %d\n", p, q, p == q);

    return 0;
}
