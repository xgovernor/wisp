// arena.c - Simple arena allocator for Wisp
#include <stdlib.h>
#include <string.h>
#include "arena.h"

#define ARENA_BLOCK_SIZE 4096

typedef struct ArenaBlock
{
    struct ArenaBlock *next;
    size_t used;
    char data[ARENA_BLOCK_SIZE];
} ArenaBlock;

struct Arena
{
    ArenaBlock *head;
};

Arena *arena_create(void)
{
    Arena *arena = malloc(sizeof(Arena));
    arena->head = NULL;
    return arena;
}

void *arena_alloc(Arena *arena, size_t size)
{
    if (!arena->head || arena->head->used + size > ARENA_BLOCK_SIZE)
    {
        ArenaBlock *block = malloc(sizeof(ArenaBlock));
        block->used = 0;
        block->next = arena->head;
        arena->head = block;
    }
    void *ptr = arena->head->data + arena->head->used;
    arena->head->used += size;
    return ptr;
}

void arena_destroy(Arena *arena)
{
    ArenaBlock *block = arena->head;
    while (block)
    {
        ArenaBlock *next = block->next;
        free(block);
        block = next;
    }
    free(arena);
}
