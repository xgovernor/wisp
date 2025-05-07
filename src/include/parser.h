#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Function to parse the tokens and construct the abstract syntax tree (AST) for the show function
void parse_show_function(Token *tokens, int token_count);

#endif // PARSER_H
