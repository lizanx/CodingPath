#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

// gcc -o main main.c -ldl
// ./main /usr/lib64/libm.so.6

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Expect one single argument pointing to the dynamic library, offered: %d\n", argc - 1);
        return EXIT_FAILURE;
    }

    void *handle = dlopen(argv[1], RTLD_NOW);
    if (!handle)
    {
        printf("Failed to open lib %s.\n", argv[1]);
        return EXIT_FAILURE;
    }

    double (*func)(double) = dlsym(handle, "sin");
    char *err = dlerror();
    if (err)
    {
        printf("Failed to get sin function, error: %s\n", err);
        goto exit_dlclose;
    }

    printf("sin(pi/2) = %lf\n", func(3.1415926 / 2));
    dlclose(handle);
    return EXIT_SUCCESS;

exit_dlclose:
    dlclose(handle);
    return EXIT_FAILURE;
}
