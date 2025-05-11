# Wisp Event Loop and Parallelism

Wisp will use a single-threaded event loop for async I/O and allow native threads for CPU-bound work, inspired by Node.js.

## Goals

- Simple async/await for I/O
- Event loop for scheduling
- Native threads for parallelism

## Example (C stub)

```c
// event_loop.h
void event_loop_run(void);
void event_loop_post(void (*fn)(void *), void *data);
```

## Next Steps

- Implement event loop in src/runtime/
- Add async/await syntax to language
