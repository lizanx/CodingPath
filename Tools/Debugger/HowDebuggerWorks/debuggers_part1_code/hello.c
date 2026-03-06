#include <stdio.h>
// #include <unistd.h>

#define MSG "hello world"

int main()
{
    puts(MSG);
    // write(STDOUT_FILENO, MSG, sizeof(MSG));

    return 0;
}
