#include <stdio.h>
#include <stdlib.h>
#include "include/parser.h"
#include "include/lexer.h"

void parse_show_function(Token *tokens, int token_count)
{
    // Simple parser logic to handle the `show` function
    if (token_count < 3)
    {
        fprintf(stderr, "Error: Invalid syntax for show function.\n");
        return;
    }

    if (tokens[0].type == TOKEN_SHOW && tokens[1].type == TOKEN_STRING && tokens[2].type == TOKEN_SEMICOLON)
    {
        // Generate code to call the show function with the provided string
        printf("Generating code for show: %s\n", tokens[1].value);
        // Here you would typically build an AST node and pass it to the code generator
    }
    else
    {
        fprintf(stderr, "Error: Expected show function syntax.\n");
    }
}
