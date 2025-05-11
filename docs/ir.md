# Wisp Intermediate Representation (IR)

This document describes the design and purpose of the Wisp IR, which is used as a portable, optimizable layer between parsing and code generation.

## Goals

- Enable optimizations before codegen
- Allow targeting multiple backends (native, JIT, WASM, etc.)
- Be simple, explicit, and easy to analyze

## Example IR Node (C struct)

```c
typedef enum {
    IR_OP_ADD,
    IR_OP_SUB,
    IR_OP_MUL,
    IR_OP_DIV,
    IR_OP_CMP,
    IR_OP_LOAD,
    IR_OP_STORE,
    // ...
} IrOp;

typedef struct IrNode {
    IrOp op;
    int dest;
    int src1;
    int src2;
    // ...
} IrNode;
```

## Next Steps

- Implement IR generation in the parser/interpreter
- Add IR optimization passes
- Add codegen backends
