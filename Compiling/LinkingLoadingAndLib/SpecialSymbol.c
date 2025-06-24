#include <stdio.h>

extern char __executable_start[];
extern char etext[], _etext[], __etext[];
extern char edata[], _edata[];
extern char end[], _end[];

int main()
{
    printf("Executable start: %#X\n", __executable_start);
    printf("Text section end: %#X %#X %#X\n", etext, _etext, __etext);
    printf("Data section end: %#X %#X\n", edata, _edata);
    printf("Executable end: %#X\n", end, _end);

    return 0;
}
