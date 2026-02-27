## Wisp Language — Complete Grammar Specification

### Lexical Rules

```ebnf
identifier        = lowercase_letter , { letter | digit | "_" } ;
type_placeholder  = uppercase_letter , { letter | digit } ;
number_literal    = digit , { digit } , [ "." , { digit } ] ;
string_literal    = '"' , { character - '"' } , '"' ;
template_literal  = "`" , { character | "{" , identifier , "}" } , "`" ;
boolean_literal   = "true" | "false" ;
comment           = "#" , { character - newline } ;
newline           = "\n" ;
indent            = INDENT ;
dedent            = DEDENT ;
```

---

### Program Structure

```ebnf
program           = { top_level_stmt } ;

top_level_stmt    = module_decl
                  | import_stmt
                  | structure_decl
                  | trait_decl
                  | implement_stmt
                  | enum_decl
                  | function_decl
                  | variable_decl
                  | constant_decl
                  | comment
                  ;
```

---

### Modules

```ebnf
module_decl       = "module" , identifier , newline ;

import_stmt       = "import" , string_literal , [ "as" , identifier ] , newline
                  | "from" , string_literal , "import" , import_list , newline ;

import_list       = identifier , { "," , identifier } ;
```

---

### Visibility

```ebnf
visibility        = "expose" | "hide" ;
```

Default is `hide` when omitted.

---

### Variables

```ebnf
variable_decl     = "let" , identifier , [ "(" , type , ")" ] , [ "is" , expression ] , newline ;
constant_decl     = "constant" , identifier , [ "(" , type , ")" ] , "is" , expression , newline ;
assignment        = "set" , identifier , "is" , expression , newline ;
```

---

### Types

```ebnf
type              = basic_type
                  | collection_type
                  | generic_type
                  | function_type
                  | type_placeholder
                  | constrained_generic
                  ;

basic_type        = numeric_type
                  | "text"
                  | char_text
                  | "bool"
                  | "nothing"
                  | "undefined"
                  ;

numeric_type      = bit_width , "bit" , "integer"
                  | bit_width , "bit" , "unsigned" , "integer"
                  | bit_width , "bit" , "decimal"
                  | short_numeric
                  ;

short_numeric     = bit_width , "bit" , "int"
                  | bit_width , "bit" , "uint"
                  | bit_width , "bit" , "float"
                  ;

bit_width         = "8" | "16" | "32" | "64" ;
char_text         = number_literal , "char" , "text" ;
collection_type   = "list" , "of" , type
                  | "map" , "of" , type , "to" , type
                  ;

generic_type      = type_placeholder ;
constrained_generic = type_placeholder , identifier ;

function_type     = "function" , "takes" , type , "returns" , type ;
```

---

### Expressions

```ebnf
expression        = logic_or ;

logic_or          = logic_and , { "or" , logic_and } ;
logic_and         = equality , { "and" , equality } ;
equality          = comparison , { ( "equals" | "not equals" ) , comparison } ;
comparison        = addition , { comparator , addition } ;
comparator        = "greater than"
                  | "less than"
                  | "at least"
                  | "at most"
                  ;

addition          = multiplication , { ( "+" | "-" ) , multiplication } ;
multiplication    = unary , { ( "*" | "/" | "%" ) , unary } ;
unary             = [ "not" | "-" ] , primary ;

primary           = number_literal
                  | string_literal
                  | template_literal
                  | boolean_literal
                  | "undefined"
                  | identifier
                  | field_access
                  | function_call
                  | array_literal
                  | tuple_literal
                  | "(" , expression , ")"
                  ;

field_access      = identifier , "." , identifier ;
array_literal     = "[" , [ expression , { "," , expression } ] , "]" ;
tuple_literal     = "(" , expression , "," , expression , { "," , expression } , ")" ;
```

---

### Functions

```ebnf
function_decl     = [ visibility ] , "function" , identifier ,
                    "(" , [ param_list ] , ")" ,
                    "returns" , type ,
                    [ "or" , "fails" ] , ":" ,
                    block ;

param_list        = param , { "," , param } ;
param             = ownership , identifier , "(" , type , ")" ;
ownership         = "own" | "borrow" | "" ;

function_call     = identifier , "(" , [ arg_list ] , ")" ;
arg_list          = expression , { "," , expression } ;

return_stmt       = "return" , expression , newline ;
```

---

### Structures

```ebnf
structure_decl    = [ visibility ] , "structure" , identifier , ":" , newline ,
                    indent ,
                    { field_decl } ,
                    { method_decl } ,
                    dedent ;

field_decl        = identifier , "(" , type , ")" , newline ;

method_decl       = "function" , identifier ,
                    "(" , self_param , { "," , param } , ")" ,
                    "returns" , type , ":" ,
                    block ;

self_param        = ownership , "self" ;

struct_init       = identifier , ":" , newline ,
                    indent ,
                    { field_init } ,
                    dedent ;

field_init        = identifier , "is" , expression , newline ;
```

---

### Traits

```ebnf
trait_decl        = [ visibility ] , "trait" , identifier , ":" , newline ,
                    indent ,
                    { trait_method } ,
                    dedent ;

trait_method      = function_decl
                  | function_signature
                  ;

function_signature = "function" , identifier ,
                     "(" , [ param_list ] , ")" ,
                     "returns" , type , newline ;

implement_stmt    = "implement" , identifier , "for" , identifier , ":" , newline ,
                    indent ,
                    { method_decl } ,
                    dedent ;
```

---

### Enums

```ebnf
enum_decl         = [ visibility ] , "enum" , identifier ,
                    [ "(" , type_placeholder , { "," , type_placeholder } , ")" ] ,
                    ":" , newline ,
                    indent ,
                    { enum_variant } ,
                    dedent ;

enum_variant      = identifier , [ "(" , type , ")" ] , newline ;
```

---

### Control Flow

```ebnf
if_stmt           = "if" , expression , ":" , block ,
                    { "otherwise" , "if" , expression , ":" , block } ,
                    [ "otherwise" , ":" , block ] ;

match_stmt        = "match" , expression , ":" , newline ,
                    indent ,
                    { when_block } ,
                    [ otherwise_block ] ,
                    dedent ;

when_block        = "when" , match_pattern , ":" , block ;
otherwise_block   = "otherwise" , ":" , block ;

match_pattern     = expression
                  | enum_variant_pattern
                  | range_pattern
                  ;

enum_variant_pattern = identifier , [ "(" , identifier , ")" ] ;
range_pattern        = expression , "to" , expression ;
```

---

### Loops

```ebnf
loop_stmt         = infinite_loop
                  | range_loop
                  | each_loop
                  ;

infinite_loop     = "loop" , ":" , block ;
range_loop        = "loop" , identifier , "from" , expression ,
                    ( "to" | "through" ) , expression ,
                    [ "step" , expression ] , ":" , block ;
each_loop         = "loop" , "each" , identifier , "in" , expression , ":" , block ;

break_stmt        = "break" , newline ;
continue_stmt     = "continue" , newline ;
```

---

### Error Handling

```ebnf
try_stmt          = "try" , ":" , block ,
                    "catch" , identifier , ":" , block ;

fail_stmt         = "fail" , expression , newline ;
inline_try        = "try" , expression , "otherwise" , expression ;
```

---

### Built-ins

```ebnf
show_stmt         = "show" , expression , newline ;
ask_stmt          = "ask" , string_literal , "as" , identifier , "(" , type , ")" , newline ;

array_method      = "push" , expression , "to" , identifier , newline
                  | "pop" , "from" , identifier , newline
                  | "length" , "of" , identifier
                  ;
```

---

### Blocks

```ebnf
block             = newline , indent , { statement } , dedent ;

statement         = variable_decl
                  | constant_decl
                  | assignment
                  | function_call , newline
                  | return_stmt
                  | if_stmt
                  | match_stmt
                  | loop_stmt
                  | break_stmt
                  | continue_stmt
                  | try_stmt
                  | fail_stmt
                  | show_stmt
                  | ask_stmt
                  | array_method
                  | comment
                  ;
```

---

### Complete locked decisions

| Feature | Decision |
|---|---|
| Statement terminator | Newline |
| Line continuation | Trailing operator or open bracket |
| Type annotation | `identifier(type)`, optional |
| Type inference | Default |
| Immutability | `constant` |
| Mutable declaration | `let` |
| Reassignment | `set` |
| Ownership | `own`, `borrow` |
| Numeric types | `8 bit integer`, `32 bit decimal` + short aliases |
| String types | `text`, `10 char text` |
| Collections | `list of Type`, `map of Type to Type` |
| Undefined | Declared not assigned |
| No-return type | `nothing` |
| Return type | `returns type` in signature |
| Conditionals | `if / otherwise if / otherwise` |
| Pattern matching | `match / when / otherwise` |
| Loops | `loop`, `from/to/through/step/each in` |
| Error handling | `try/catch`, `fail`, `or fails`, `try x otherwise y`, `Result` enum |
| Operators | Config toggle, `gt+tab` snippet expansion |
| Comments | `#` single line |
| Structures | `structure`, `self`, `own self` / `borrow self` |
| Contracts | `trait`, `implement X for Y` |
| Generics | Capitalized placeholders, constrained by trait name |
| Enums | `enum` with algebraic variants |
| Visibility | `expose` / `hide`, private by default |
| Modules | File-as-module, optional `module` declaration |

---
