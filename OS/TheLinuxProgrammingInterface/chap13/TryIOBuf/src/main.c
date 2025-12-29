#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

static const char g_msg1[] = "Hello world!";
static const char g_msg2[] = "TLPI is a great book!";

int main(int argc, char *argv[])
{
    if (argc != 3)
        usageErr("program <file 1> <file 2>\n");

    const char *f1 = argv[1];
    const char *f2 = argv[2];

    FILE *fp1 = fopen(f1, "w");
    if (!fp1)
        errExit("Failed to open %s", f1);
    char buf[128];
    memset(buf, 0, sizeof(buf));
    if (setvbuf(fp1, buf, _IOFBF, sizeof(buf)))
    {
        fclose(fp1);
        errExit("Failed to set buffer for %s.", f1);
    }
    fwrite(g_msg1, sizeof(char), strlen(g_msg1), fp1);
    fwrite(g_msg2, sizeof(char), strlen(g_msg2), fp1);
    fprintf(stdout, "Buffer content: %s\n", buf);
    fflush(fp1);
    fsync(fileno(fp1));
    fclose(fp1);

    FILE *fp2 = fopen(f2, "w");
    if (!fp2)
        errExit("Failed to open %s", f2);
    if (setvbuf(fp2, NULL, _IONBF, 0))
    {
        fclose(fp2);
        errExit("Failed to set no buffer for %s.", f2);
    }
    fwrite(g_msg1, sizeof(char), strlen(g_msg1), fp2);
    fwrite(g_msg2, sizeof(char), strlen(g_msg2), fp2);
    fflush(fp2);
    fdatasync(fileno(fp2));
    fclose(fp2);

    return 0;
}
