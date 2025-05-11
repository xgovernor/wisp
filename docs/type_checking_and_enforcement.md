# Wisp Type Checking and Enforcement

## Overview
Wisp enforces strict type checking for all variable assignments and reassignments. Once a variable is declared with a type, any subsequent assignment must use the exact same type. This is enforced both in the symbol table and at the interpreter level for clear error reporting.

## Rules
- **Type must match exactly**: Assigning a value of a different type to an existing variable results in a type error.
- **Constants cannot be reassigned**: Any attempt to reassign a constant variable results in an error.
- **Type is checked on every assignment**: Both at initial declaration and on reassignment.

## Example
```wisp
let foo(16 bit unsigned number) is 123;
foo(16 bit unsigned number) is 456; // OK
foo(32 bit float) is 3.14; // Error: type mismatch

constant bar(8 bit unsigned number) is 42;
bar(8 bit unsigned number) is 99; // Error: constant reassignment
```

## Error Messages
- Type errors are reported with the variable name, expected type, and provided type.
- Constant reassignment errors are reported with the variable name.

## Implementation Notes
- The symbol table checks type on every assignment and logs errors using the central logger.
- The interpreter also checks type before calling the symbol table, for better error location.

## Edge Cases
- Type names must match exactly (including whitespace and case).
- Reassigning with a different type, even if compatible, is not allowed (future work may allow type coercion).
- Uninitialized variables or undeclared variables are handled as errors elsewhere in the interpreter.

## Testing
See `tests/type_error_test.wisp` for sample cases.
