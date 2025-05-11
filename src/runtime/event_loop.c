// event_loop.c - Simple event loop stub for Wisp
#include "event_loop.h"
#include <stdio.h>
void event_loop_run(void)
{
    printf("[Wisp Event Loop] Running (stub)\n");
}
void event_loop_post(void (*fn)(void *), void *data)
{
    printf("[Wisp Event Loop] Posting task (stub)\n");
    fn(data);
}
