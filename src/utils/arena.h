// arena.h - Arena allocator interface
#ifndef WISP_ARENA_H
#define WISP_ARENA_H
#include <stddef.h>
typedef struct Arena Arena;
Arena *arena_create(void);
void *arena_alloc(Arena *arena, size_t size);
void arena_destroy(Arena *arena);
#endif // WISP_ARENA_H
