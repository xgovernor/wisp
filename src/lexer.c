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
        if (input[position] == 's' && strncmp(&input[position], "show", 4) == 0)
        {
            position += 4;
            Token *token = malloc(sizeof(Token));
            token->type = TOKEN_SHOW;
            token->value = NULL;
            return token;
        }
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
