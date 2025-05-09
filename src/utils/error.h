#ifndef WISP_ERROR_H
#define WISP_ERROR_H

#include <stdio.h>

/**
 * @brief Print a formatted error message with file, line, and context.
 *
 * @param file The source file name (use __FILE__)
 * @param line The line number (use __LINE__)
 * @param fmt  The printf-style format string
 * @param ...  Arguments for the format string
 */
void wisp_error(const char *file, int line, const char *fmt, ...);

#define WISP_ERROR(fmt, ...) wisp_error(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif // WISP_ERROR_H
