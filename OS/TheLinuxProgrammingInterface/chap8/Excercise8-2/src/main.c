#define _DEFAULT_SOURCE
#include <pwd.h>
#include <stdio.h>
#include "tlpi_hdr.h"

static struct passwd *custom_getpwnam(const char *name)
{
    if (!name)
        return NULL;

    struct passwd *pwd = NULL;
    setpwent();
    while ((pwd = getpwent()) != NULL)
    {
        if (strcmp(pwd->pw_name, name) == 0)
            break;
    }
    endpwent();
    return pwd;
}

static void PrintPwdInfo(const struct passwd *pwd)
{
    printf("User name: %s\n", pwd->pw_name);
    printf("Encrypted password: %s\n", pwd->pw_passwd);
    printf("User ID: %u\n", pwd->pw_uid);
    printf("Group ID: %u\n", pwd->pw_gid);
    printf("Comment(user info): %s\n", pwd->pw_gecos);
    printf("User home dir: %s\n", pwd->pw_dir);
    printf("User shell: %s\n", pwd->pw_shell);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        cmdLineErr("program <user name>");

    struct passwd *pwd = custom_getpwnam(argv[1]);
    if (!pwd)
        printf("No entry found.\n");
    else
        PrintPwdInfo(pwd);

    return 0;
}
