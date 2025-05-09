#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "symbol_table.h"
#include "../utils/utils.h"
#include "../utils/error.h"

int wisp_interpret(const char *source, const char *filename)
{
    (void)filename; // Mark unused for now
    if (!source)
    {
        WISP_ERROR("No source code provided to interpreter.");
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
                WISP_ERROR("Syntax error: expected variable name after let/constant");
                if (name_token)
                    free_token(name_token);
                had_error = 1;
                continue;
            }
            char varname[MAX_NAME_LEN];
            strncpy(varname, name_token->value, MAX_NAME_LEN - 1);
            varname[MAX_NAME_LEN - 1] = '\0';
            free_token(name_token);
            Token *typedef_token = get_next_token(NULL);
            if (!typedef_token || typedef_token->type != TOKEN_TYPEDEF)
            {
                WISP_ERROR("Syntax error: expected type definition in () after variable name");
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
                WISP_ERROR("Syntax error: expected 'is' after type definition");
                if (is_token)
                    free_token(is_token);
                had_error = 1;
                continue;
            }
            free_token(is_token);
            Token *value_token = get_next_token(NULL);
            if (!value_token || (value_token->type != TOKEN_STRING && value_token->type != TOKEN_NUMBER && value_token->type != TOKEN_IDENTIFIER))
            {
                WISP_ERROR("Syntax error: expected value after 'is'");
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
                WISP_ERROR("Syntax error: expected string after show");
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
