#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

#define BUFFER_SIZE (1024 * 1024) // 1MiB

static void show_page_faults()
{
    struct rusage usage;
    int ret = getrusage(RUSAGE_SELF, &usage);
    if (ret < 0)
    {
        perror("Failed to get page fault info");
    }
    else
    {
        printf("Major page faults: %ld | Minor page faults: %ld\n", usage.ru_majflt, usage.ru_minflt);
    }
}

int main(int argc, char *argv[])
{
    printf("=== Before any allocation ===\n");
    show_page_faults();

    printf("=== After malloc ===\n");
    char *buf = malloc(BUFFER_SIZE);
    if (!buf)
    {
        perror("Failed to malloc");
        exit(-1);
    }
    show_page_faults();

    printf("=== After memset ===\n");
    memset(buf, 0, BUFSIZ);
    show_page_faults();

    printf("=== After 2nd memset ===\n");
    memset(buf, 0xff, BUFSIZ);
    show_page_faults();

    return 0;
}
