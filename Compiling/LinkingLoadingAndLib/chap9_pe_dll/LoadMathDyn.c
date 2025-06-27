#include <Windows.h>
#include <stdio.h>

typedef double (*Func)(double, double);

int main(int argc, char *argv[])
{
    // Load dll
    HINSTANCE libHandle = LoadLibrary("Math.dll");
    if (!libHandle)
    {
        printf("Failed to load Math.dll\n");
        return EXIT_FAILURE;
    }

    // Get function pointer
    Func f = (Func)GetProcAddress(libHandle, "Add");
    if (!f)
    {
        printf("Failed to get function Add\n");
        FreeLibrary(libHandle);
        return EXIT_FAILURE;
    }

    printf("2 + 3 = %lf\n", f(2., 3.));

    FreeLibrary(libHandle);

    return EXIT_SUCCESS;
}
