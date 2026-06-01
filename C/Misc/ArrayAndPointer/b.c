#include <stdio.h>
#include <string.h>

// Doesn't comply with the actual type 'char[1024]':
// - For 'char buf[1024]', 'buf' directly stores the data, no pointer indirection.
// - For 'char *buf', 'buf' stores an address which points to where the data is stored.
// In 'strcpy', 'buf' is considered a pointer, first 8bytes of 'buf' are read and dereferenced,
// but they're all '0's -> dereference causes SIGV.
extern char *buf;

// Correction: declare the variable with compliant type.
// extern char buf[];

int main(void)
{
    strcpy(buf, "Hello World!"); // SEGV
    printf("%s\n", buf);
    return 0;
}
