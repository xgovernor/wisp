### Language Semantics

#### Purpose:

- Develop a high performance general purpose programming language that mimics human language like syntactical grammar.

#### Basic rule and practices:

- Instead of `{}`, our language will use `:` and indentation like Python language.
- In the end of lines, this language will use `;` like C, JavaScript, etc language.
- This language is strongly typed language. So user must have to define type within `()`.

### Importing library & Modules

```
import '<library_name>' // Import the library.
import '<library_name>' as <alias>; // Import library with alias.
from '<library_name>' import <module_1>, <module_2>; // Import modules from a library.
from "<library_name>" import < module_1, module_2, module_3 > as <alias>;

```

#### Basic Data Types

| Type                        | Description                     | Example                                                                                  |
| --------------------------- | ------------------------------- | ---------------------------------------------------------------------------------------- |
| signed 32bit integer number | To define integer numbers.      | let n1(unsigned 32bit number)                                                            |
| floating number             | To define floating number.      | let n2(32 bit floating number)                                                           |
| string                      | To define string.               | let name(50 character string) is "Abu Taher Muhammad"                                    |
| boolean                     | To define boolean yes/no value. | let status(boolean) is true                                                              |
| array                       | To define array.                | let numbers(array) is [1, 2, 3, 4, 5]                                                    |
| object                      | To define object.               | let person(object) is { name: "Abu Taher Muhammad", age: 25.6 }                          |
| function                    | To define function.             | let function add takes x(32 bit number), y(32 bit number) returns (32 bit number): x + y |
| null                        | To define null value.           | let value(null) is null                                                                  |
| undefined                   | To define undefined value.      | let value(undefined) is undefined                                                        |

### Basic variable declarations

```

let name is "Abu Taher Muhammad";
let age(32 bit floating number); // (32 bit floating number) is the type of a variable

age is 25.6;

```

#### Arithmetic Operators

| Sign                              | Name           | Description                            | Example          |
| --------------------------------- | -------------- | -------------------------------------- | ---------------- |
| +                                 | Addition       | Adds together two values               | x + y            |
| -                                 | Subtraction    | Subtracts one value from another       | x - y            |
| \*                                | Multiplication | Multiplies two values                  | x \* y           |
| /                                 | Division       | Divides one value by another           | x / y            |
| %                                 | Modulus        | Returns the division remainder         | x % y            |
| <variable increase by <a number>  | Increment      | Increases the value of a variable by 1 | increase x by 1; |
| decrease <variable> by <a number> | Decrement      | Decreases the value of a variable by 1 | decrease x by 1; |

#### Assignment Operator

<!-- This need to be finalize. -->

| Operator | Example | Same As    |
| -------- | ------- | ---------- |
| is       | x is 5  | x=5        |
| +=       | x += 3  | x = x + 3  |
| -=       | x -= 3  | x = x - 3  |
| \_=      | x \_= 3 | x = x \* 3 |
| /=       | x /= 3  | x = x / 3  |
| %=       | x %= 3  | x = x % 3  |
| &=       | x &= 3  | x = x & 3  |
| ^=       | x ^= 3  | x = x ^ 3  |
| >>=      | x >>= 3 | x = x >> 3 |
| <<=      | x <<= 3 | x = x << 3 |

#### Comparison Operators

| Operator            | Name                     | Description                                                                 |
| ------------------- | ------------------------ | --------------------------------------------------------------------------- |
| equal to            | Equal to                 | Returns 1 if the values are equal                                           |
| not equal to        | Not equal                | Returns 1 if the values are not equal                                       |
| greater than        | Greater than             | Returns 1 if the first value is greater than the second value               |
| less than           | Less than                | Returns 1 if the first value is less than the second value                  |
| greater or equal to | Greater than or equal to | Returns 1 if the first value is greater than, or equal to, the second value |
| less or equal to    | Less than or equal to    | Returns 1 if the first value is less than, or equal to, the second value    |

### Logical Operator

#### Operators

| Operator | Name | Example                                  | Description                                      |
| -------- | ---- | ---------------------------------------- | ------------------------------------------------ |
| and      | AND  | x less than 5 and x less than 10         | Returns 1 if both statements are true            |
| or       | OR   | x less than 5 or x less than 4           | Returns 1 if one of the statements is true       |
| not      | NOT  | x not less than 5 and x not less than 10 | Reverse the result, returns 0 if the result is 1 |

#### Examples: Basic conditions similar to `if...else`

Example-1:

```

let a(32bit unsigned number) is 5;
let b(32bit unsigne number) is 10;

if a greater than b:
    show `{a} is greater`;
else if a less than b:
    show `{b} is greater`;
else:
    show `Something is is wrong!`'

```

int a = 5;
int b = 10;

if (a > b) {
printf("%d is greater", a);
} else if (a<b) {
printf("%d is greater", b);
} {
printf("%d is greater", b);
}

#### Example-2: Shorthand conditional smilar to `(condition) ? expressionTrue : expressionFalse;`

```

let age is 16;

if age greater or equal to 18 than show `You are an adult person` or else show `You are not adult`;

```

### Loop

#### Example-1: while loop

```

let countdown(32 bit unsigned number) is 3;

while countdown greater than 0:
    show `{countdown}`;
    countdown post decrease by 1;

show `Happy New Year!!\n`;

```

#### Example-2: do...while loop

```

let i(32 bit number) is 0;

do:
    show `{i}`;
    i post increase by 1;
while i less than 5;

```

#### Example-3: For loop

```

let i(32 bit number);

for i is 0; i less then 5; i post increase by 1:
    show `{i}`;

```

#### Example-4: Nested loop

```

let i(32 bit number), j(32 bit number);

// Outer loop
for i is 1; i less or equal to 2; i pre increase by 1:
    show `Outer: {i}`; // Executes 2 times

    // Inner loop
    for j is 1; j less or equal to 3; j pre increase by 1:
        show `Inner: {j}; // Executes 6 times (2 \* 3)

```

#### Example-5: Continue/break

```

let i(32 bit number) is 0;

for i is 0; i less than 5; i post increase by 1:
    if i is 2:
        continue;
    if i is 4:
        break;

    show `{i}`;

```

### Array

#### Example-1: Accessing Elements

```

let numbers(array) is [1, 2, 3, 4, 5];

show `Numbers: {numbers}`;
show `Number on 1st position: {numbers[0]}`;

```

#### Example-2: Modifying Elements

```

let numbers(array) is [1, 2, 3, 4, 5];

show `Numbers: {numbers}`;
numbers[0] is 10;
show `Number on 1st position: {numbers[0]}`;

```

#### Array: Methods

| Function                    | Description                               | Example            |
| --------------------------- | ----------------------------------------- | ------------------ |
| `length of`                 | To get the length of an array.            | length of numbers  |
| `push <element> to <array>` | To add an element to the end of an array. | push 6 to numbers; |
| `pop from <array>`          | To remove the last element from an array. | pop from numbers;  |

### User Input

```
ask "what is your name?" as name(20 character string);
```

Here,

- Ask prompts to the user for input.
- "..." is a placeholder for the user's response.
- `name` is a variable that will store the user's input.

### File I/O and External Interaction

Consider built-in functions for reading/writing files, networking, etc.

### Math and Utility Functions

Built-in math functions: min, max, abs, round, etc.

### Date and Time

Built-in support for date/time manipulation.

### Concurrency

If you want to support modern programming, consider how to handle concurrency: async, await, or similar constructs.

### Standard Library

Outline what will be included in the standard library.

## Keywords|

| Keyword   | Description                                                                       |
| --------- | --------------------------------------------------------------------------------- |
| break     | Breaks out of a loop or a switch block                                            |
| case      | Marks a block of code in switch statements                                        |
| let       | Defines a variable                                                                |
| const     | Defines a constant variable (unchangeable)                                        |
| continue  | Continues to the next iteration of a loop                                         |
| default   | Specifies the default block of code in a switch statement                         |
| do        | Used together with while to create a do/while loop                                |
| else      | Used in conditional statements                                                    |
| enum      | Declares an enumerated type                                                       |
| for       | Creates a for loop                                                                |
| if        | Makes a conditional statement                                                     |
| return    | Used to return a value from a function                                            |
| sizeof    | An operator that returns the amount of memory occupied by a variable or data type |
| structure | Defines a structure                                                               |
| switch    | Selects one of many code blocks to be executed                                    |
| while     | Creates a while loop                                                              |
| do        | Used together with while to create a do/while loop                                |
| show      | To print something to user like `print()` in python language.                     |
| run       | To run a function or a block of code.                                             |
| ask       | To prompt the user for input.                                                     |

#### Comments

Use `#` for single-line comments:

```

```
