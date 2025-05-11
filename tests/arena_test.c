// arena_test.c - Test cases for Wisp arena allocator
#include "../src/utils/arena.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct { int x; double y; } TestStruct;

int main(void) {
    // Basic allocation
    Arena *arena = arena_create();
    assert(arena != NULL);
    int *a = (int *)arena_alloc(arena, sizeof(int));
    *a = 42;
    assert(*a == 42);

    // Allocate multiple objects
    TestStruct *ts = (TestStruct *)arena_alloc(arena, sizeof(TestStruct));
    ts->x = 7; ts->y = 3.14;
    assert(ts->x == 7 && ts->y == 3.14);

    // Allocate more than block size
    void *big = arena_alloc(arena, 5000);
    assert(big != NULL);

    // Zero-size allocation (should not crash)
    void *zero = arena_alloc(arena, 0);
    // Accept either NULL or valid pointer, but must not crash

    // Destroy fresh arena (no allocations)
    Arena *empty = arena_create();
    arena_destroy(empty);

    // Destroy arena with allocations
    arena_destroy(arena);

    // Double destroy (should not crash, but is undefined)
    // arena_destroy(arena); // Uncomment to test, but not recommended

    printf("Arena allocator tests passed.\n");
    return 0;
}
