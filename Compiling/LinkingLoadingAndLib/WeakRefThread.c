// #include <stdio.h>
#include <pthread.h>

int pthread_create(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *) __attribute__((weakref));

int main()
{
    if (pthread_create)
    {
        // printf("Running in multi-thread environment!\n");
        return 1;
    }
    else
    {
        // printf("Running in single-thread environment!\n");
        return 2;
    }
}
