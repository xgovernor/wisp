
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "interpreter.h"
#include "../lexer/lexer.h" // Use the lexer.h with comparison tokens
#include "symbol_table.h"
#include "../utils/utils.h"
#include "../utils/error.h"

// Simple helper to parse a number from a string (int or float)
static double parse_number(const char *s)
{
    if (!s)
        return 0.0;
    return atof(s);
}

// Evaluate a binary comparison expression: left <op> right
static int eval_comparison(TokenType op, const char *left, const char *right)
{
    double l = parse_number(left);
    double r = parse_number(right);
    switch (op)
    {
    case TOKEN_EQUAL_TO:
        return l == r;
    case TOKEN_NOT_EQUAL_TO:
        return l != r;
    case TOKEN_GREATER_THAN:
        return l > r;
    case TOKEN_LESS_THAN:
        return l < r;
    case TOKEN_GREATER_EQUAL:
        return l >= r;
    case TOKEN_LESS_EQUAL:
        return l <= r;
    default:
        return 0;
    }
}
#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include "../lexer/lexer.h"
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
    int first = 1;
    int had_error = 0;
    Token *left = NULL, *op = NULL, *right = NULL, *semi = NULL;
    while ((left = get_next_token(first ? source : NULL)) && left->type != TOKEN_EOF)
    {
        first = 0;
        // Only handle: <number|identifier/boolean> <comparison_op> <number|identifier/boolean> ;
        if ((left->type == TOKEN_NUMBER || left->type == TOKEN_IDENTIFIER || left->type == TOKEN_TRUE || left->type == TOKEN_FALSE))
        {
            op = get_next_token(NULL);
            if (op && (op->type == TOKEN_EQUAL_TO || op->type == TOKEN_NOT_EQUAL_TO || op->type == TOKEN_GREATER_THAN || op->type == TOKEN_LESS_THAN || op->type == TOKEN_GREATER_EQUAL || op->type == TOKEN_LESS_EQUAL))
            {
                right = get_next_token(NULL);
                if (right && (right->type == TOKEN_NUMBER || right->type == TOKEN_IDENTIFIER || right->type == TOKEN_TRUE || right->type == TOKEN_FALSE))
                {
                    semi = get_next_token(NULL);
                    if (semi && semi->type == TOKEN_SEMICOLON)
                    {
                        // Lookup variable values if needed, handle booleans
                        const char *lval = NULL;
                        if (left->type == TOKEN_IDENTIFIER)
                            lval = (find_variable(left->value) ? find_variable(left->value)->value : "0");
                        else if (left->type == TOKEN_TRUE)
                            lval = "1";
                        else if (left->type == TOKEN_FALSE)
                            lval = "0";
                        else
                            lval = left->value;

                        const char *rval = NULL;
                        if (right->type == TOKEN_IDENTIFIER)
                            rval = (find_variable(right->value) ? find_variable(right->value)->value : "0");
                        else if (right->type == TOKEN_TRUE)
                            rval = "1";
                        else if (right->type == TOKEN_FALSE)
                            rval = "0";
                        else
                            rval = right->value;

                        int result = eval_comparison(op->type, lval, rval);
                        printf("%s\n", result ? "1" : "0");
                        free_token(left);
                        free_token(op);
                        free_token(right);
                        free_token(semi);
                        continue;
                    }
                    if (semi)
                        free_token(semi);
                }
                if (right)
                    free_token(right);
            }
            if (op)
                free_token(op);
        }
        // Fallback to original interpreter logic
        if (left->type == TOKEN_LET || left->type == TOKEN_CONSTANT)
        {
            int is_const = (left->type == TOKEN_CONSTANT);
            free_token(left);
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
            // Collect tokens after 'is' up to semicolon for possible expression assignment
            Token *assign_tokens[8];
            int assign_tok_count = 0;
            Token *assign_tok = NULL;
            while ((assign_tok = get_next_token(NULL)) && assign_tok->type != TOKEN_SEMICOLON && assign_tok->type != TOKEN_EOF && assign_tok_count < 8)
            {
                assign_tokens[assign_tok_count++] = assign_tok;
            }
            // DEBUG: Print tokens collected after 'is'
            printf("[DEBUG] Assignment tokens after 'is': ");
            for (int i = 0; i < assign_tok_count; ++i) {
                printf("%d ", assign_tokens[i]->type);
            }
            printf("\n");
            int assigned = 0;
            if (assign_tok_count == 1)
            {
                Token *value_token = assign_tokens[0];
                if (value_token->type == TOKEN_TRUE)
                {
                    add_variable(varname, vartype, "1", is_const);
                    assigned = 1;
                }
                else if (value_token->type == TOKEN_FALSE)
                {
                    add_variable(varname, vartype, "0", is_const);
                    assigned = 1;
                }
                else if (value_token->type == TOKEN_STRING || value_token->type == TOKEN_NUMBER || value_token->type == TOKEN_IDENTIFIER)
                {
                    add_variable(varname, vartype, value_token->value, is_const);
                    assigned = 1;
                }
            }
            else if (assign_tok_count == 3 &&
                     (assign_tokens[1]->type == TOKEN_EQUAL_TO || assign_tokens[1]->type == TOKEN_NOT_EQUAL_TO ||
                      assign_tokens[1]->type == TOKEN_GREATER_THAN || assign_tokens[1]->type == TOKEN_LESS_THAN ||
                      assign_tokens[1]->type == TOKEN_GREATER_EQUAL || assign_tokens[1]->type == TOKEN_LESS_EQUAL))
            {
                // Simple binary comparison: <left> <op> <right>
                const char *lval = NULL;
                if (assign_tokens[0]->type == TOKEN_IDENTIFIER)
                {
                    Variable *var = find_variable(assign_tokens[0]->value);
                    lval = (var ? var->value : "0");
                }
                else if (assign_tokens[0]->type == TOKEN_TRUE)
                {
                    lval = "1";
                }
                else if (assign_tokens[0]->type == TOKEN_FALSE)
                {
                    lval = "0";
                }
                else
                {
                    lval = assign_tokens[0]->value;
                }
                const char *rval = NULL;
                if (assign_tokens[2]->type == TOKEN_IDENTIFIER)
                {
                    Variable *var = find_variable(assign_tokens[2]->value);
                    rval = (var ? var->value : "0");
                }
                else if (assign_tokens[2]->type == TOKEN_TRUE)
                {
                    rval = "1";
                }
                else if (assign_tokens[2]->type == TOKEN_FALSE)
                {
                    rval = "0";
                }
                else
                {
                    rval = assign_tokens[2]->value;
                }
                int result = eval_comparison(assign_tokens[1]->type, lval, rval);
                add_variable(varname, vartype, result ? "1" : "0", is_const);
                assigned = 1;
            }
            for (int i = 0; i < assign_tok_count; ++i)
                free_token(assign_tokens[i]);
            if (assign_tok)
                free_token(assign_tok);
            if (!assigned)
            {
                WISP_ERROR("Syntax error: expected value or valid expression after 'is'");
                had_error = 1;
            }
            continue;
        }
        if (left->type == TOKEN_SHOW)
        {
            free_token(left);
            // Collect tokens until semicolon
            Token *tokens[64];
            int tok_count = 0;
            Token *tok = NULL;
            while ((tok = get_next_token(NULL)) && tok->type != TOKEN_SEMICOLON && tok->type != TOKEN_EOF && tok_count < 64)
            {
                tokens[tok_count++] = tok;
            }
            // Evaluate the expression (for now, only handle single token or simple comparison)
            if (tok_count == 1)
            {
                Token *t = tokens[0];
                switch (t->type)
                {
                case TOKEN_STRING:
                    printf("%s\n", interpolate(t->value));
                    break;
                case TOKEN_NUMBER:
                    printf("%s\n", t->value);
                    break;
                case TOKEN_TRUE:
                    printf("true\n");
                    break;
                case TOKEN_FALSE:
                    printf("false\n");
                    break;
                case TOKEN_IDENTIFIER:
                {
                    Variable *var = find_variable(t->value);
                    if (var)
                    {
                        if (strcmp(var->type, "boolean") == 0)
                        {
                            if (strcmp(var->value, "1") == 0)
                                printf("true\n");
                            else
                                printf("false\n");
                        }
                        else
                        {
                            printf("%s\n", var->value);
                        }
                    }
                    else
                    {
                        printf("<undefined>\n");
                    }
                    break;
                }
                default:
                    printf("<unknown>\n");
                    break;
                }
            }
            else if (tok_count == 3 &&
                     (tokens[1]->type == TOKEN_EQUAL_TO || tokens[1]->type == TOKEN_NOT_EQUAL_TO ||
                      tokens[1]->type == TOKEN_GREATER_THAN || tokens[1]->type == TOKEN_LESS_THAN ||
                      tokens[1]->type == TOKEN_GREATER_EQUAL || tokens[1]->type == TOKEN_LESS_EQUAL))
            {
                // Simple binary comparison: <left> <op> <right>
                const char *lval = NULL;
                if (tokens[0]->type == TOKEN_IDENTIFIER)
                {
                    Variable *var = find_variable(tokens[0]->value);
                    lval = (var ? var->value : "0");
                }
                else if (tokens[0]->type == TOKEN_TRUE)
                {
                    lval = "1";
                }
                else if (tokens[0]->type == TOKEN_FALSE)
                {
                    lval = "0";
                }
                else
                {
                    lval = tokens[0]->value;
                }
                const char *rval = NULL;
                if (tokens[2]->type == TOKEN_IDENTIFIER)
                {
                    Variable *var = find_variable(tokens[2]->value);
                    rval = (var ? var->value : "0");
                }
                else if (tokens[2]->type == TOKEN_TRUE)
                {
                    rval = "1";
                }
                else if (tokens[2]->type == TOKEN_FALSE)
                {
                    rval = "0";
                }
                else
                {
                    rval = tokens[2]->value;
                }
                int result = eval_comparison(tokens[1]->type, lval, rval);
                printf("%s\n", result ? "true" : "false");
            }
            else
            {
                printf("<unsupported show expression>\n");
            }
            // Free tokens
            for (int i = 0; i < tok_count; ++i)
                free_token(tokens[i]);
            if (tok)
                free_token(tok);
            continue;
        }
        free_token(left);
    }
    if (left)
        free_token(left);
    return had_error ? 1 : 0;
}
