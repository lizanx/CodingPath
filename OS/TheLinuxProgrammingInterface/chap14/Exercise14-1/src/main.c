#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include "tlpi_hdr.h"

#define ID_MAX 999999

static void CreateOrOverrideFile(const char *file)
{
    if (!file)
        errExit("Failed to create file due to invalid file path.");

    FILE *fp = fopen(file, "w");
    if (!fp)
        errExit("Failed to open %s", file);
    fwrite("*", 1, 1, fp);
    fclose(fp);
}

static int CompareUnsigned(const void *a, const void *b)
{
    unsigned x = *((const unsigned *)a);
    unsigned y = *((const unsigned *)b);
    if (x > y)
        return 1;
    if (x < y)
        return -1;
    return 0;
}

static void DeleteFile(const char *file)
{
    if (!file)
        return;

    errno = 0;
    if (unlink(file))
    {
        if (errno != ENOENT)
            errExit("Failed to remove file %s", file);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        usageErr("program <dir path> <file cnt>");

    const char *dir = argv[1];
    int count = atoi(argv[2]);
    if (count <= 0 || count > (ID_MAX + 1))
        errExit("File count must be in range (0, %u]", ID_MAX);

    unsigned *idList = malloc(sizeof(unsigned) * count);
    if (!idList)
        errExit("Failed to allocate memory for id list.");

    for (int i = 0; i < count; ++i)
    {
        unsigned id;
        if (getrandom(&id, sizeof(id), 0) != sizeof(id))
            errExit("Failed to get random id.");

        if (id > ID_MAX)
            --i;
        else
            idList[i] = id;
    }

    qsort(idList, count, sizeof(unsigned), CompareUnsigned);

    size_t bufLen = strlen(dir) + strlen("xNNNNNN") + 2;
    char *filePath = malloc(bufLen);
    if (!filePath)
        errExit("Failed to allocate buffer for file path.");

    for (int i = 0; i < count; ++i)
    {
        snprintf(filePath, bufLen, "%s/x%.6u", dir, idList[i]);
        CreateOrOverrideFile(filePath);
    }

    // qsort(idList, count, sizeof(unsigned), CompareUnsigned);

    for (int i = 0; i < count; ++i)
    {
        snprintf(filePath, bufLen, "%s/x%.6u", dir, idList[i]);
        DeleteFile(filePath);
    }

    free(filePath);
    free(idList);

    return 0;
}
