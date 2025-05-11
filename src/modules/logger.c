// logger.c - Wisp Logger Module Implementation
#include "logger.h"
#include <time.h>

// You can set this to control the minimum log level at runtime
enum
{
    WISP_LOG_LEVEL = WISP_LOG_DEBUG
};

// get_label is currently unused, but kept for future extensibility.
#if 0
static const char *get_label(int level)
{
    switch (level)
    {
    case WISP_LOG_ERROR:
        return WISP_LABEL_ERROR;
    case WISP_LOG_WARN:
        return WISP_LABEL_WARN;
    case WISP_LOG_INFO:
        return WISP_LABEL_INFO;
    case WISP_LOG_DEBUG:
        return WISP_LABEL_DEBUG;
    default:
        return "[Wisp Log]";
    }
}
#endif

// Utility for timestamp (used in templates)
const char *wisp_log_time(void)
{
    static char timebuf[20];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
    return timebuf;
}

void wisp_log(int level, const char *file, int line, const char *func, const char *fmt, ...)
{
    if (level > WISP_LOG_LEVEL)
        return;
    const char *label = NULL;
    switch (level)
    {
    case WISP_LOG_ERROR:
        label = WISP_LABEL_ERROR;
        break;
    case WISP_LOG_WARN:
        label = WISP_LABEL_WARN;
        break;
    case WISP_LOG_INFO:
        label = WISP_LABEL_INFO;
        break;
    case WISP_LOG_DEBUG:
        label = WISP_LABEL_DEBUG;
        break;
    case WISP_LOG_SUCCESS:
        label = WISP_LABEL_SUCCESS;
        break;
    case WISP_LOG_TRACE:
        label = WISP_LABEL_TRACE;
        break;
    default:
        label = "[Wisp Log]";
        break;
    }
    va_list args;
    va_start(args, fmt);
    // Print label, timestamp, and context for all logs
    fprintf(stderr, "%s %s %s:%d:%s: ", label, wisp_log_time(), file, line, func);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}
