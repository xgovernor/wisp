// type_error_test.wisp - Tests for strict type enforcement in Wisp
let foo(16 bit unsigned number) is 123;
foo(16 bit unsigned number) is 456; // OK
foo(32 bit float) is 3.14; // Should error: type mismatch
let bar(10 character string) is "hello";
bar(10 character string) is "world"; // OK
bar(16 bit unsigned number) is 789; // Should error: type mismatch
constant baz(8 bit unsigned number) is 42;
baz(8 bit unsigned number) is 99; // Should error: constant reassignment
