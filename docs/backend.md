# Wisp Backend Abstraction

Wisp will support multiple code generation backends (native, JIT, WASM, etc.) via a backend abstraction layer.

## Goals

- Allow easy addition of new targets
- Enable cross-compilation
- Support both AOT and JIT

## Example Backend API (C)

```c
typedef struct Backend {
    void (*emit)(const IrNode *ir, size_t count);
    // ...
} Backend;
```

## Next Steps

- Implement backend interface in codebase
- Add native and JIT stubs
