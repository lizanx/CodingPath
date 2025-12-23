#define _DEFAULT_SOURCE
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    long userNameLengthMax = sysconf(_SC_LOGIN_NAME_MAX);
    if (userNameLengthMax < 0)
        userNameLengthMax = 256;
    char *userName = malloc(userNameLengthMax);
    if (!userName)
        errExit("Failed to alloc memory for user name.");
    printf("User name: ");
    fflush(stdout);
    if (fgets(userName, userNameLengthMax, stdin) == NULL)
        errExit("Failed to get user name input.");
    size_t userNameLength = strlen(userName);
    if (userName[userNameLength - 1] == '\n')
        userName[userNameLength - 1] = '\0';
    struct passwd *pwd = getpwnam(userName);
    if (!pwd)
        errExit("Failed to get pwd by user name.");
    struct spwd *spwd = getspnam(userName);
    if (!spwd && errno == EACCES)
        errExit("Failed to get spwd by user name.");
    if (spwd)
        pwd->pw_passwd = spwd->sp_pwdp;
    free(userName);
    userName = NULL;

    char *password = getpass("Password: ");
    char *encrypted = crypt(password, pwd->pw_passwd);
    for (char *p = password; *p; ++p)
        *p = '\0';
    if (!encrypted)
        errExit("Failed to get encryption.");
    bool authOk = strcmp(encrypted, pwd->pw_passwd) == 0;
    if (!authOk)
    {
        printf("Incorrect password.\n");
        exit(EXIT_FAILURE);
    }

    printf("Successfully authenticated: UID = %ld\n", (long)pwd->pw_uid);

    return 0;
}
