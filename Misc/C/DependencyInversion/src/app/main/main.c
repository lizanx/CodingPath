#include "logger_interface.h"
#include "file_logger.h"
#include "stdout_logger.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    logger_interface_t *flogger = make_file_logger("my_file_logger");
    if (!flogger)
    {
        fprintf(stderr, "Failed to create file logger!");
        return -1;
    }
    flogger->init();

    logger_interface_t *clogger = make_stdout_logger("my_console_logger");
    if (!clogger)
    {
        fprintf(stderr, "Failed to create console logger!");
        return -2;
    }
    clogger->init();

    flogger->log(flogger->name, "Hello world!");
    clogger->log(clogger->name, "Hello world!");

    free(flogger);
    free(clogger);

    return 0;
}
