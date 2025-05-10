# Wisp Language: EBNF Suggestions & Implementation Plan

## 1. Improved Function Syntax

```ebnf
function_decl = "function" , identifier , "takes" , param_list, ":" , block ;
param         = identifier , "(" , type , ")" , [ "=" , expression ] ;
param_list    = param , { "," , param } , [ "," , "..." , identifier ] ;
return_stmt   = "return" , expression , "as" , "(" , type , ")" , ";" ;
```

## 2. Optional/Default/Variadic Parameters

```ebnf
param         = identifier , "(" , type , ")" , [ "=" , expression ] ;
param_list    = param , { "," , param } , [ "," , "..." , identifier ] ;
```

## 3. Union, Optional, and Generic Types

```ebnf
type          = basic_type | array_type | object_type | function_type | union_type | generic_type | optional_type ;
union_type    = type , "|" , type ;
generic_type  = identifier , "<" , type , { "," , type } , ">" ;
optional_type = type , "?" ;
```

## 4. Pattern Matching & Destructuring

```ebnf
match_stmt    = "match" , expression , ":" , { pattern_block } ;
pattern_block = pattern , ":" , block ;
pattern       = expression | destructure_pattern ;
destructure_pattern = array_pattern | object_pattern ;
array_pattern = "[" , [ identifier , { "," , identifier } ] , "]" ;
object_pattern= "{" , [ identifier , { "," , identifier } ] , "}" ;
```

## 5. Lambda/Anonymous Functions

```ebnf
lambda_expr   = "function" , [ param_list ] , "=>" , expression ;
```

## 6. Pipe/Chaining Operators

```ebnf
pipe_expr     = expression , { "|>" , expression } ;
```

## 7. Range Expressions

```ebnf
range_expr    = expression , ".." , expression ;
```

## 8. Error Handling

```ebnf
try_stmt      = "try" , block , [ "catch" , identifier , block ] , [ "finally" , block ] ;
throw_stmt    = "throw" , expression , ";" ;
```

## 9. Async/Concurrency

```ebnf
async_fn_decl = "async" , function_decl ;
await_expr    = "await" , expression ;
spawn_stmt    = "spawn" , expression , ";" ;
```

## 10. Multi-line and Doc Comments

```ebnf
multiline_comment = "/*" , { character - "*/" } , "*/" ;
doc_comment       = "///" , { character - "\n" } ;
```

---

# Implementation Guideline

1. **Lexer**

   - Add new tokens for `|>`, `..`, `=>`, `?`, `<`, `>`, `|`, `...`, `/* ... */`, `///`, etc.
   - Recognize multi-line and doc comments.
   - Support indentation tokens (INDENT/DEDENT).

2. **Parser**

   - Update function parsing to support new syntax (including async, default/variadic params, return type in return statement).
   - Add parsing rules for union, optional, and generic types.
   - Implement pattern matching and destructuring in parser.
   - Add support for lambda expressions and pipe/chaining.
   - Add error handling constructs (try/catch/finally, throw).
   - Add async/await/spawn constructs.

3. **Type Checker**

   - Extend type system to support unions, generics, and optionals.
   - Enforce return type in return statements.
   - Type-check destructuring and pattern matching.

4. **Code Generation/Runtime**

   - Implement runtime support for async/await, error handling, and pattern matching.
   - Optimize for memory and performance (e.g., string interning, efficient data structures).

5. **Standard Library**

   - Add built-in functions for array/object methods, math, concurrency, and error handling.

6. **Documentation & Testing**
   - Update documentation and examples for new features.
   - Add tests for all new grammar constructs and edge cases.

---

**Tip:**

- Implement incrementally: start with function/return improvements, then add types, then pattern matching, then error handling, then async/concurrency.
- Write example code for each new feature to guide parser and runtime development.

If you want EBNF for a specific feature or a more detailed breakdown, let me know!
