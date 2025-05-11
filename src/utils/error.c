#include "error.h"
#include "../modules/logger.h"
#include <stdarg.h>
#include <stdio.h>

void wisp_error(const char *file, int line, const char *fmt, ...)
{
    // Deprecated: Use central logger instead
    va_list args;
    va_start(args, fmt);
    wisp_log(WISP_LOG_ERROR, file, line, "?", fmt, args);
    va_end(args);
}
