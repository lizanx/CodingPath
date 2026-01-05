#define _DEFAULT_SOURCE
#include <sys/xattr.h>
#include <time.h>
#include "tlpi_hdr.h"

#define XATTR_OWNER_NAME "user.owner"
#define XATTR_OWNER_VALUE "lizan"
#define XATTR_CREATED_TIME_NAME "user.created_at"
#define XATTR_NON_EXISTED_NAME "user.non_existed_xattr"

int main(int argc, char *argv[])
{
    if (argc != 2)
        usageErr("program <file>");

    const char *file = argv[1];

    char bufXattrValue[256];

    strncpy(bufXattrValue, XATTR_OWNER_VALUE, sizeof(bufXattrValue));
    if (setxattr(file, XATTR_OWNER_NAME, bufXattrValue, strlen(bufXattrValue), 0))
        errExit("Failed to set xattr %s\n", XATTR_OWNER_NAME);

    time_t now = time(NULL);
    strncpy(bufXattrValue, ctime(&now), sizeof(bufXattrValue));
    if (setxattr(file, XATTR_CREATED_TIME_NAME, bufXattrValue, strlen(bufXattrValue), 0))
        errExit("Failed to set xattr %s\n", XATTR_CREATED_TIME_NAME);

    ssize_t n = getxattr(file, XATTR_OWNER_NAME, bufXattrValue, sizeof(bufXattrValue));
    if (n < 0)
        errExit("Failed to get xattr %s\n", XATTR_OWNER_NAME);
    if (n >= sizeof(bufXattrValue))
        errExit("Buf size not enough for xattr %s\n", XATTR_OWNER_NAME);
    bufXattrValue[n] = '\0';
    if (strcmp(bufXattrValue, XATTR_OWNER_VALUE) == 0)
        printf("%s xattr checked: %s\n", XATTR_OWNER_NAME, bufXattrValue);
    else
        printf("Unmatched value '%s' for xattr %s\n", bufXattrValue, XATTR_OWNER_NAME);

    n = getxattr(file, XATTR_CREATED_TIME_NAME, bufXattrValue, sizeof(bufXattrValue));
    if (n < 0)
        errExit("Failed to get xattr %s\n", XATTR_CREATED_TIME_NAME);
    if (n >= sizeof(bufXattrValue))
        errExit("Buf size not enough for xattr %s\n", XATTR_CREATED_TIME_NAME);
    bufXattrValue[n] = '\0';
    printf("Value for xattr '%s': %s\n", XATTR_CREATED_TIME_NAME, bufXattrValue);

    n = getxattr(file, XATTR_NON_EXISTED_NAME, bufXattrValue, sizeof(bufXattrValue));
    if (n < 0)
        printf("%s xattr checked.(doesn't exist)\n", XATTR_NON_EXISTED_NAME);
    else
        printf("[ERROR] Value for xattr '%s': %s\n", XATTR_NON_EXISTED_NAME, bufXattrValue);

    return 0;
}
