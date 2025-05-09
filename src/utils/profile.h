// profile.h - Simple timing macros for profiling
#ifndef PROFILE_H
#define PROFILE_H
#include <stdio.h>
#include <time.h>

#define PROFILE_START(name)                   \
    struct timespec name##_start, name##_end; \
    clock_gettime(CLOCK_MONOTONIC, &name##_start)

#define PROFILE_END(name, label)                                                                                           \
    clock_gettime(CLOCK_MONOTONIC, &name##_end);                                                                           \
    double name##_elapsed = (name##_end.tv_sec - name##_start.tv_sec) + (name##_end.tv_nsec - name##_start.tv_nsec) / 1e9; \
    fprintf(stderr, "[PROFILE] %s: %.6f sec\n", label, name##_elapsed)

#endif // PROFILE_H
