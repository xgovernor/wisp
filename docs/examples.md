# Examples

## Basic Example

```lang
let name(30 character string) is "Abu Taher Muhammad";
let age(16 bit unsigned number) is 26;
let city(20 character string) is "Dhaka";
let country(20 character string) is "Bangladesh";
constant pi(32 bit float) is 3.14159;

show `Hello, {name}! Looks like you are {age}`;
show `You live in {city}, {country}.`;
show `Pi is approximately {pi}`;
```

## Variable and Constant Reassignment

```lang
let temp(10 character string) is "first";
show `Temp: {temp}`;
let temp(10 character string) is "second";
show `Temp: {temp}`;

constant const_val(8 bit unsigned number) is 100;
show `Const: {const_val}`;
constant const_val(8 bit unsigned number) is 200; // Error or ignored
show `Const: {const_val}`;
```

## Comments

```lang
// This is a single-line comment
/* This is a
multi-line comment */
```
