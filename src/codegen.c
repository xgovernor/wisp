#include <stdio.h>
#include "codegen.h"

void generate_show_function(const char* message) {
    // Generate LLVM IR for the show function
    printf("Calling show with message: %s\n", message);
    // Here you would typically generate the LLVM IR code
    // For demonstration, we just print the message
}