// Variable and function definitions
let name(20 character string) is "Muhammad";
const institute(50 character long) is "Metropolitan University";
let age(32 bit unsigned number) is 20;
let not_exported(10 char) is "hidden";

// Exporting single module
export let age(32 bit unsigned number) is 20;

// Exporting multiple modules
export modules name, institute;

// Exporting undefined symbol (should error)
export modules does_not_exist;

// Exporting duplicate symbol (should error or warn)
export modules name;


// Invalid export syntax (should error)
export let;
export modules;

show `hi`;
