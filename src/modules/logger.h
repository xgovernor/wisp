// logger.h - Wisp Logger Module
#ifndef WISP_LOGGER_H
#define WISP_LOGGER_H

#include <stdio.h>
#include <stdarg.h>

// Log levels
#define WISP_LOG_ERROR 1
#define WISP_LOG_WARN 2
#define WISP_LOG_INFO 3
#define WISP_LOG_DEBUG 4
#define WISP_LOG_SUCCESS 5
#define WISP_LOG_TRACE 6

// Log label strings (bold, colored)
#define WISP_LABEL_ERROR "\033[1;31m[Wisp Error]\033[0m"
#define WISP_LABEL_WARN "\033[1;33m[Wisp Warn]\033[0m"
#define WISP_LABEL_INFO "\033[1;36m[Wisp Info]\033[0m"
#define WISP_LABEL_DEBUG "\033[1;35m[Wisp Debug]\033[0m"
#define WISP_LABEL_SUCCESS "\033[1;32m[Wisp Success]\033[0m"
#define WISP_LABEL_TRACE "\033[1;34m[Wisp Trace]\033[0m"

// Log label strings (bold, colored)
#define WISP_LABEL_ERROR "\033[1;31m[Wisp Error]\033[0m"
#define WISP_LABEL_WARN "\033[1;33m[Wisp Warn]\033[0m"
#define WISP_LABEL_INFO "\033[1;36m[Wisp Info]\033[0m"
#define WISP_LABEL_DEBUG "\033[1;35m[Wisp Debug]\033[0m"

// Error log template (optimized for clarity and guidance)
#define WISP_ERROR_TEMPLATE      \
    "%s %s %s:%d:%s: (%s) %s\n"  \
    "  File:    %s\n"            \
    "\n"                         \
    "  Problem:\n    %s\n"       \
    "\n"                         \
    "  Details:\n    %s\n"       \
    "\n"                         \
    "  Suggested Fixes:\n%s\n"   \
    "\n"                         \
    "  For more help, see: %s\n" \
    "------------------------------------------------------------"

// Utility for timestamp
const char *wisp_log_time(void);

// Convenience macro for full error logs
#define WISP_LOGE_FULL(errcode, errtype, file_path, problem, details, fixes, help_url) \
    wisp_log(WISP_LOG_ERROR, __FILE__, __LINE__, __func__, WISP_ERROR_TEMPLATE,        \
             WISP_LABEL_ERROR, wisp_log_time(), __FILE__, __LINE__, __func__, errcode, errtype, file_path, problem, details, fixes, help_url)

// Central logger API
void wisp_log(int level, const char *file, int line, const char *func, const char *fmt, ...);

// DRY: Unified log macros for all log types
#define WISP_LOGE(fmt, ...) wisp_log(WISP_LOG_ERROR, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define WISP_LOGW(fmt, ...) wisp_log(WISP_LOG_WARN, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define WISP_LOGI(fmt, ...) wisp_log(WISP_LOG_INFO, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define WISP_LOGD(fmt, ...) wisp_log(WISP_LOG_DEBUG, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define WISP_LOGS(fmt, ...) wisp_log(WISP_LOG_SUCCESS, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define WISP_LOGT(fmt, ...) wisp_log(WISP_LOG_TRACE, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#endif // WISP_LOGGER_H
