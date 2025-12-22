#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

#define ENV_ITEM_CNT 128

extern char **environ;

static char *env_items[ENV_ITEM_CNT] = {NULL};

static void substitute_env_ptr()
{
    if (environ != env_items)
    {
        size_t i = 0;
        for (char **old_env = environ; *old_env != NULL; ++old_env, ++i)
        {
            if (i == ENV_ITEM_CNT)
                errExit("Too many env items!");

            char *item = malloc(strlen(*old_env) + 1);
            if (!item)
                errExit("Failed to allocate memory to substitute envs.\n");

            strcpy(item, *old_env);
            env_items[i] = item;
        }
        environ = env_items;
    }
}

static void modify_env_item(char **env_item, const char *name, const char *value)
{
    free(*env_item);
    size_t name_len = strlen(name);
    size_t value_len = strlen(value);
    *env_item = malloc(name_len + value_len + 2);
    if (!*env_item)
        errExit("Failed to allocate memory for env item update.");
    strcpy(*env_item, name);
    (*env_item)[name_len] = '=';
    strcpy(*env_item + name_len + 1, value);
}

static int custom_setenv(const char *name, const char *value, int override)
{
    if (!name || !value)
        errExit("Invalid name or value.");

    substitute_env_ptr();
    // size_t name_len = strlen(name);
    // size_t value_len = strlen(value);
    char **env = env_items;
    for (; *env != NULL; ++env)
    {
        bool name_matched = true;
        const char *env_item = *env;
        for (const char *new_item_name = name; *env_item != '\0' && *new_item_name != '\0'; ++env_item, ++new_item_name)
        {
            if (*env_item != *new_item_name)
            {
                name_matched = false;
                break;
            }
        }
        if (name_matched && *env_item == '=') // Env already set, modify it.
        {
            if (override)
                modify_env_item(env, name, value);
            return 0;
        }
    }
    // Not found, add new entry.
    if (env - env_items > ENV_ITEM_CNT - 1)
        errExit("Not enough entries in env_items.");
    modify_env_item(env, name, value);
    return 0;
}

static int custom_unsetenv(const char *name)
{
    substitute_env_ptr();
    // size_t name_len = strlen(name);
    char **env = env_items;
    for (; *env != NULL; ++env)
    {
        const char *item = *env;
        const char *name_tmp = name;
        for (; *item && *name_tmp; ++item, ++name_tmp)
        {
            if (*item != *name_tmp)
                break;
        }
        if (!*name_tmp && *item && *item == '=') // name found
        {
            free(*env);
            while (*env)
            {
                *env = *(env + 1);
                ++env;
            }
            return 0;
        }
    }
    return 0;
}

static void print_all_env_var()
{
    for (char **env = environ; *env; ++env)
        printf("%s\n", *env);
}

int main(int argc, char *argv[])
{
    printf("Initially, env vars:\n");
    print_all_env_var();
    printf("\n\n");

    custom_setenv("GREET", "HelloWorld", 0);
    char *greet = getenv("GREET");
    if (greet)
        printf("Get ENV[GREET] = %s\n", greet);
    else
        errExit("Failed to get greet(1).");
    printf("After set [GREET] to [HelloWorld], env vars:\n");
    print_all_env_var();
    printf("\n\n");

    custom_setenv("GREET", "Nice to meet you", 1);
    greet = getenv("GREET");
    if (greet)
        printf("Get ENV[GREET] = %s\n", greet);
    else
        errExit("Failed to get greet(2).");
    printf("After set [GREET] to [Nice to meet you], env vars:\n");
    print_all_env_var();
    printf("\n\n");

    custom_unsetenv("GREET");
    greet = getenv("GREET");
    if (greet)
        errExit("Still get ENV[GREET] after unset it!");
    else
        printf("ENV[GREET] successfully unset.\n");
    printf("After unset ENV[GREET], env vars:\n");
    print_all_env_var();
    printf("\n\n");

    return 0;
}
