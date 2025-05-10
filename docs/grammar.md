# Wisp Language Grammar (EBNF)

This document defines the formal grammar for the Wisp programming language, designed to be English-like, memory-optimized, and performant.

---

## Lexical Structure

```ebnf
identifier      = letter , { letter | digit | "_" } ;
number_literal  = digit , { digit } [ "." , digit , { digit } ] ;
string_literal  = '"' , { character - '"' } , '"' ;
boolean_literal = "true" | "false" ;
null_literal    = "null" ;
undefined_literal = "undefined" ;
comment         = "#" , { character - "\n" } ;
```

---

## Program Structure

```ebnf
program         = { statement } ;

statement       = import_stmt
                | variable_decl
                | assignment
                | function_decl
                | if_stmt
                | while_stmt
                | do_while_stmt
                | for_stmt
                | switch_stmt
                | show_stmt
                | run_stmt
                | ask_stmt
                | break_stmt
                | continue_stmt
                | return_stmt
                | comment
                ;
```

---

## Importing

```ebnf
import_stmt     = "import" , string_literal , [ "as" , identifier ] , ";"
                | "from" , string_literal , "import" , import_list , [ "as" , identifier ] , ";" ;
import_list     = identifier , { "," , identifier } ;
```

---

## Variable Declaration & Assignment

```ebnf
variable_decl   = "let" , identifier , [ "(" , type , ")" ] , [ "is" , expression ] , ";"
                | "const" , identifier , [ "(" , type , ")" ] , [ "is" , expression ] , ";" ;

assignment      = identifier , "is" , expression , ";" ;
```

---

## Types

```ebnf
type            = basic_type | array_type | object_type | function_type ;
basic_type      = "boolean" | "string" | "array" | "object" | "null" | "undefined"
                | "unsigned" , number_size , "bit" , "number"
                | number_size , "bit" , "floating" , "number"
                | number_size , "character" , "string"
                ;
number_size     = digit , { digit } ;

array_type      = "array" ;
object_type     = "object" ;
function_type   = "function" , identifier , "takes" , param_list , "returns" , "(" , type , ")" ;

param_list      = identifier , "(" , type , ")" , { "," , identifier , "(" , type , ")" } ;
```

---

## Expressions

```ebnf
expression      = logic_or ;

logic_or        = logic_and , { "or" , logic_and } ;
logic_and       = equality , { "and" , equality } ;
equality        = comparison , { ( "equal to" | "not equal to" ) , comparison } ;
comparison      = addition , { ( "greater than" | "less than" | "greater or equal to" | "less or equal to" ) , addition } ;
addition        = multiplication , { ( "+" | "-" ) , multiplication } ;
multiplication  = unary , { ( "*" | "/" | "%" ) , unary } ;
unary           = [ "not" | "-" ] , primary ;
primary         = number_literal
                | string_literal
                | boolean_literal
                | null_literal
                | undefined_literal
                | identifier
                | array_literal
                | object_literal
                | "(" , expression , ")"
                ;

array_literal   = "[" , [ expression , { "," , expression } ] , "]" ;
object_literal  = "{" , [ object_entry , { "," , object_entry } ] , "}" ;
object_entry    = identifier , ":" , expression ;
```

---

## Control Flow

```ebnf
if_stmt         = "if" , expression , ":" , block , [ "else if" , expression , ":" , block ] , [ "else" , ":" , block ] ;
while_stmt      = "while" , expression , ":" , block ;
do_while_stmt   = "do" , ":" , block , "while" , expression , ";" ;
for_stmt        = "for" , identifier , "is" , expression , ";" , expression , ";" , assignment , ":" , block ;
switch_stmt     = "switch" , expression , ":" , { case_block } , [ default_block ] ;
case_block      = "case" , expression , ":" , block ;
default_block   = "default" , ":" , block ;

break_stmt      = "break" , ";" ;
continue_stmt   = "continue" , ";" ;
return_stmt     = "return" , expression , "as" , "(" , type , ")" , ";" ;

block           = INDENT , { statement } , DEDENT ;
```

---

## Functions

```ebnf
function_decl   = "function" , identifier , "takes" , param_list , ":" , block ;

run_stmt        = "run" , identifier , "(" , [ arg_list ] , ")" , ";" ;
arg_list        = expression , { "," , expression } ;
```

---

## Show/Ask

```ebnf
show_stmt       = "show" , string_literal , ";" ;
ask_stmt        = "ask" , string_literal , "as" , identifier , "(" , type , ")" , ";" ;
```

---

## Array Methods

```ebnf
array_method    = "length of" , identifier
                | "push" , expression , "to" , identifier , ";"
                | "pop from" , identifier , ";"
                ;
```

---

## Comments

```ebnf
comment         = "#" , { character - "\n" } ;
```

---

## Indentation

- INDENT and DEDENT are tokens produced by the lexer based on indentation, similar to Python.

---

## Notes

- **Indentation:** Blocks are defined by indentation (INDENT/DEDENT tokens), not `{}`.
- **End of Statement:** Each statement ends with a `;`.
- **Types:** Types are always specified in parentheses after variable names.
- **English-like Operators:** Use `greater than`, `less than`, `equal to`, etc., for comparisons.
- **Keywords:** As listed in your doc, including `let`, `const`, `if`, `else`, `for`, `while`, `do`, `switch`, `case`, `default`, `break`, `continue`, `return`, `show`, `ask`, `run`, etc.
- **Comments:** Use `#` for single-line comments.

---

This grammar is a living document and should be updated as the language evolves.
