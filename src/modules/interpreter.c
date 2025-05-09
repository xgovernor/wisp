#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "symbol_table.h"
#include "../utils/utils.h"

int wisp_interpret(const char *source, const char *filename)
{
    if (!source)
    {
        fprintf(stderr, "No source code provided to interpreter.\n");
        return 1;
    }
    Token *token = NULL;
    int first = 1;
    int had_error = 0;
    while ((token = get_next_token(first ? source : NULL)) && token->type != TOKEN_EOF)
    {
        first = 0;
        if (token->type == TOKEN_LET || token->type == TOKEN_CONSTANT)
        {
            int is_const = (token->type == TOKEN_CONSTANT);
            free_token(token);
            Token *name_token = get_next_token(NULL);
            if (!name_token || name_token->type != TOKEN_IDENTIFIER)
            {
                fprintf(stderr, "Syntax error: expected variable name after let/constant\n");
                if (name_token)
                    free_token(name_token);
                had_error = 1;
                continue;
            }
            char varname[MAX_NAME_LEN];
            strncpy(varname, name_token->value, MAX_NAME_LEN);
            free_token(name_token);
            Token *typedef_token = get_next_token(NULL);
            if (!typedef_token || typedef_token->type != TOKEN_TYPEDEF)
            {
                fprintf(stderr, "Syntax error: expected type definition in () after variable name\n");
                if (typedef_token)
                    free_token(typedef_token);
                had_error = 1;
                continue;
            }
            char vartype[MAX_TYPE_LEN];
            strncpy(vartype, typedef_token->value, MAX_TYPE_LEN);
            free_token(typedef_token);
            Token *is_token = get_next_token(NULL);
            if (!is_token || is_token->type != TOKEN_IS)
            {
                fprintf(stderr, "Syntax error: expected 'is' after type definition\n");
                if (is_token)
                    free_token(is_token);
                had_error = 1;
                continue;
            }
            free_token(is_token);
            Token *value_token = get_next_token(NULL);
            if (!value_token || (value_token->type != TOKEN_STRING && value_token->type != TOKEN_NUMBER && value_token->type != TOKEN_IDENTIFIER))
            {
                fprintf(stderr, "Syntax error: expected value after 'is'\n");
                if (value_token)
                    free_token(value_token);
                had_error = 1;
                continue;
            }
            add_variable(varname, vartype, value_token->value, is_const);
            free_token(value_token);
            Token *semi_token = get_next_token(NULL);
            if (semi_token)
                free_token(semi_token);
            continue;
        }
        if (token->type == TOKEN_SHOW)
        {
            free_token(token);
            Token *string_token = get_next_token(NULL);
            if (string_token && string_token->type == TOKEN_STRING)
            {
                printf("%s\n", interpolate(string_token->value));
                free_token(string_token);
                Token *semi_token = get_next_token(NULL);
                free_token(semi_token);
            }
            else
            {
                fprintf(stderr, "\033[31mSyntax error: expected string after show\033[0m\n");
                if (string_token)
                    free_token(string_token);
                had_error = 1;
            }
            continue;
        }
        free_token(token);
    }
    if (token)
        free_token(token);
    return had_error ? 1 : 0;
}
