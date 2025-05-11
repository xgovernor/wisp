# Wisp Comparison Operators

Wisp supports English-like comparison operators for expressive, readable code. These operators can be used in conditions, expressions, and variable assignments.

## Supported Operators

| Operator              | Name                     | Description                                                                 |
| --------------------- | ------------------------ | --------------------------------------------------------------------------- |
| `equal to`            | Equal to                 | Returns 1 if the values are equal                                           |
| `not equal to`        | Not equal                | Returns 1 if the values are not equal                                       |
| `greater than`        | Greater than             | Returns 1 if the first value is greater than the second value               |
| `less than`           | Less than                | Returns 1 if the first value is less than the second value                  |
| `greater or equal to` | Greater than or equal to | Returns 1 if the first value is greater than, or equal to, the second value |
| `less or equal to`    | Less than or equal to    | Returns 1 if the first value is less than, or equal to, the second value    |

## Example Usage

```wisp
let a(32 bit number) is 5;
let b(32 bit number) is 10;

if a greater than b:
    show `{a} is greater`;
else if a less than b:
    show `{b} is greater`;
else if a equal to b:
    show `They are equal`;

# Direct evaluation
5 greater than 3;
# Output: 1

5 less than 3;
# Output: 0

5 equal to 5;
# Output: 1

5 not equal to 5;
# Output: 0
```

## Notes

- These operators work with both numbers and variables.
- The result is `1` (true) or `0` (false).
- You can use them in conditions, assignments, or direct expressions.

---

For more details, see the main language documentation or the interpreter source code.
