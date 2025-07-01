#include <stdio.h>

#define SECNAME ".CRT$XCG"
#pragma section(SECNAME, long, read)

void foo()
{
    printf("Hello ");
}

typedef void(__cdecl *_PVFV)();
__declspec(allocate(SECNAME)) _PVFV dummy[] = {foo};

int main()
{
    printf("World\n");

    return 0;
}
