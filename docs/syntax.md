# Syntax Guide

## Variable Declaration

```
let var_name(type) is value;
```

Example:

```
let age(16 bit unsigned number) is 26;
let name(30 character string) is "Alice";
```

## Constant Declaration

```
constant const_name(type) is value;
```

Example:

```
constant pi(32 bit float) is 3.14159;
```

## Print Statement

```
show `Hello, {name}!`;
```

- Use backtick-quoted strings for template interpolation.
- Use `{variable}` to insert variable values.

## Comments

- Single-line: `// This is a comment`
- Multi-line: `/* This is a
multi-line comment */`
