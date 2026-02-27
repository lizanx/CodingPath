#include <stdlib.h>
#include <stdio.h>
#include "stdout_logger.h"

static const char *g_logger_file = "log.txt";

static void init_stdout_logger()
{
}

static void log_stdout_logger(const char *logger_name, const char *msg)
{
    fprintf(stdout, "[%s] %s\n", logger_name, msg);
}

logger_interface_t *make_stdout_logger(const char *name)
{
    logger_interface_t *logger = malloc(sizeof(logger_interface_t));
    if (!logger)
        return logger;

    logger->name = name;
    logger->init = init_stdout_logger;
    logger->log = log_stdout_logger;

    return logger;
}
