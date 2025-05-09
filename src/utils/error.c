#include "error.h"
#include <stdarg.h>
#include <stdio.h>

void wisp_error(const char *file, int line, const char *fmt, ...)
{
    fprintf(stderr, "\033[31m[Wisp Error] %s:%d: ", file, line);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\033[0m\n");
}
