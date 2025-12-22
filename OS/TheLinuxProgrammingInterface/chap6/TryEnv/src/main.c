#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

extern char **environ;

int main(int argc, char *argv[])
{
    printf("=============== Show current environment variables ===============\n");
    for (char **env = environ; *env != NULL; ++env)
    {
        printf("Env: ^^^%s^^^\n", *env);
    }

    printf("\n=============== Get certain environment vars ===============\n");
    char *env = getenv("SHELL");
    if (env)
        printf("Current shell: %s\n", env);
    env = getenv("CPPFLAGS");
    if (env)
        printf("CPPFLAGS: %s\n", env);
    else
        printf("CPPFLAGS not set.\n");
    env = getenv("HOME");
    if (env)
        printf("User home dir: %s\n", env);
    else
        printf("No user home dir found!\n");

    printf("\n=============== Set env vars ===============\n");
    char buf[32] = "GREET=Nice to meet you";
    if (putenv(buf))
        errExit("Failed to putenv.");
    env = getenv("GREET");
    printf("Env[GREET]: %s\n", env);
    strncpy(buf, "GREET=Hello world", sizeof(buf) - 1);
    buf[31] = '\0';
    printf("Env[GREET]: %s\n", env); // This changes, since "putenv" only saves a pointer rather copy the env var string.
    if (setenv("GREET2", buf, 0))
        errExit("Failed to setenv.\n");
    env = getenv("GREET2");
    printf("Env[GREET2]: %s\n", env);
    strncpy(buf, "Nice to meet you", sizeof(buf) - 1);
    buf[31] = '\0';
    env = getenv("GREET2");
    printf("Env[GREET2]: %s\n", env); // This won't change even if buf changed, because "setenv" will copy the env string rather than just save a pointer.

    return 0;
}
