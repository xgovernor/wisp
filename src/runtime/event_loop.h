// event_loop.h - Event loop interface for Wisp
#ifndef WISP_EVENT_LOOP_H
#define WISP_EVENT_LOOP_H
void event_loop_run(void);
void event_loop_post(void (*fn)(void *), void *data);
#endif // WISP_EVENT_LOOP_H
