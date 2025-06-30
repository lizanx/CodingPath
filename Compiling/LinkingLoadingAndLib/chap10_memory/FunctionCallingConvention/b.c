#include <stdio.h>

// Calling convention customization are usually available only on X86.
// On X86_64/ARM, calling convention is defined by system ABI, considered not customizable.
void __attribute__((cdecl)) foo(int a, int b)
{
    printf("a = %d, b = %d\n", a, b);
}
