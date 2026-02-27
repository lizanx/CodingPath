#include <stdlib.h>
#include <stdio.h>
#include "file_logger.h"

static const char *g_logger_file = "log.txt";

static void init_stdout_logger()
{
    FILE *filp = fopen(g_logger_file, "w");
    if (filp)
        fclose(filp);
}

static void log_stdout_logger(const char *logger_name, const char *msg)
{
    FILE *filp = fopen(g_logger_file, "a");
    if (filp)
    {
        fprintf(filp, "[%s] %s\n", logger_name, msg);
        fclose(filp);
    }
}

logger_interface_t *make_file_logger(const char *name)
{
    logger_interface_t *logger = malloc(sizeof(logger_interface_t));
    if (!logger)
        return logger;

    logger->name = name;
    logger->init = init_stdout_logger;
    logger->log = log_stdout_logger;

    return logger;
}
