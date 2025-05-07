#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/lexer.h"

static const char *input = NULL;
static size_t position = 0;

Token *get_next_token(const char *source)
{
    if (source != NULL)
    {
        input = source;
        position = 0;
    }
    while (input[position] != '\0')
    {
        // Skip whitespace
        if (input[position] == ' ' || input[position] == '\t' || input[position] == '\n' || input[position] == '\r')
        {
            position++;
            continue;
        }
        // Skip single-line comments (// ...)
        if (input[position] == '/' && input[position + 1] == '/')
        {
            position += 2;
            while (input[position] != '\0' && input[position] != '\n')
            {
                position++;
            }
            continue;
        }
        // Skip multi-line comments (/* ... */)
        if (input[position] == '/' && input[position + 1] == '*')
        {
            position += 2;
            while (input[position] != '\0' && !(input[position] == '*' && input[position + 1] == '/'))
            {
                position++;
            }
            if (input[position] == '*' && input[position + 1] == '/')
            {
                position += 2;
            }
            continue;
        }
        // Keywords
        if (strncmp(&input[position], "show", 4) == 0 && (input[position + 4] == ' ' || input[position + 4] == '`'))
        {
            position += 4;
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_SHOW;
            token->value = NULL;
            return token;
        }
        if (strncmp(&input[position], "let", 3) == 0 && (input[position + 3] == ' ' || input[position + 3] == '('))
        {
            position += 3;
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_LET;
            token->value = NULL;
            return token;
        }
        if (strncmp(&input[position], "constant", 8) == 0 && (input[position + 8] == ' ' || input[position + 8] == '('))
        {
            position += 8;
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_CONSTANT;
            token->value = NULL;
            return token;
        }
        if (strncmp(&input[position], "is", 2) == 0 && (input[position + 2] == ' ' || input[position + 2] == '"' || input[position + 2] == '\'' || input[position + 2] == '-' || (input[position + 2] >= '0' && input[position + 2] <= '9')))
        {
            position += 2;
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_IS;
            token->value = NULL;
            return token;
        }
        // String literal (template string)
        if (input[position] == '`')
        {
            position++;
            size_t start = position;
            while (input[position] != '`' && input[position] != '\0')
            {
                position++;
            }
            if (input[position] == '`')
            {
                size_t length = position - start;
                char *value = malloc(length + 1);
                strncpy(value, &input[start], length);
                value[length] = '\0';
                position++;
                Token *token = malloc(sizeof(Token));
                token->type = TOKEN_STRING;
                token->value = value;
                return token;
            }
        }
        // Double-quoted string literal (for variable assignment)
        if (input[position] == '"')
        {
            position++;
            size_t start = position;
            while (input[position] != '"' && input[position] != '\0')
            {
                position++;
            }
            if (input[position] == '"')
            {
                size_t length = position - start;
                char *value = malloc(length + 1);
                strncpy(value, &input[start], length);
                value[length] = '\0';
                position++;
                Token *token = malloc(sizeof(Token));
                token->type = TOKEN_STRING;
                token->value = value;
                return token;
            }
        }
        // Braces for template variables
        if (input[position] == '{')
        {
            position++;
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_LBRACE;
            token->value = NULL;
            return token;
        }
        if (input[position] == '}')
        {
            position++;
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_RBRACE;
            token->value = NULL;
            return token;
        }
        // Parentheses for type definitions
        if (input[position] == '(')
        {
            size_t start = ++position;
            int paren_count = 1;
            while (input[position] != '\0' && paren_count > 0)
            {
                if (input[position] == '(')
                    paren_count++;
                else if (input[position] == ')')
                    paren_count--;
                position++;
            }
            size_t length = position - start - 1; // exclude closing ')'
            char *value = malloc(length + 1);
            strncpy(value, &input[start], length);
            value[length] = '\0';
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_TYPEDEF;
            token->value = value;
            return token;
        }
        // Numbers (support negative and floating point)
        if ((input[position] == '-' && (input[position + 1] >= '0' && input[position + 1] <= '9')) || (input[position] >= '0' && input[position] <= '9'))
        {
            size_t start = position;
            if (input[position] == '-')
                position++;
            int has_dot = 0;
            while (1)
            {
                if (input[position] >= '0' && input[position] <= '9')
                {
                    position++;
                }
                else if (input[position] == '.' && !has_dot)
                {
                    has_dot = 1;
                    position++;
                }
                else
                {
                    break;
                }
            }
            size_t length = position - start;
            char *value = malloc(length + 1);
            strncpy(value, &input[start], length);
            value[length] = '\0';
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_NUMBER;
            token->value = value;
            return token;
        }
        // Identifiers (variable names)
        if ((input[position] >= 'a' && input[position] <= 'z') || (input[position] >= 'A' && input[position] <= 'Z') || input[position] == '_')
        {
            size_t start = position;
            while ((input[position] >= 'a' && input[position] <= 'z') ||
                   (input[position] >= 'A' && input[position] <= 'Z') ||
                   (input[position] >= '0' && input[position] <= '9') ||
                   input[position] == '_')
            {
                position++;
            }
            size_t length = position - start;
            char *value = malloc(length + 1);
            strncpy(value, &input[start], length);
            value[length] = '\0';
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_IDENTIFIER;
            token->value = value;
            return token;
        }
        // Numbers (support negative and floating point)
        if ((input[position] == '-' && (input[position + 1] >= '0' && input[position + 1] <= '9')) || (input[position] >= '0' && input[position] <= '9'))
        {
            size_t start = position;
            if (input[position] == '-')
                position++;
            int has_dot = 0;
            while ((input[position] >= '0' && input[position] <= '9') || (!has_dot && input[position] == '.'))
            {
                if (input[position] == '.')
                    has_dot = 1;
                position++;
            }
            size_t length = position - start;
            char *value = malloc(length + 1);
            strncpy(value, &input[start], length);
            value[length] = '\0';
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_NUMBER;
            token->value = value;
            return token;
        }
        if (input[position] == ';')
        {
            position++;
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_SEMICOLON;
            token->value = NULL;
            return token;
        }
        position++;
    }
    Token *token = malloc(sizeof(Token));
    token->type = TOKEN_EOF;
    token->value = NULL;
    return token;
}

void free_token(Token *token)
{
    if (token)
    {
        if (token->value)
            free(token->value);
        free(token);
    }
}
