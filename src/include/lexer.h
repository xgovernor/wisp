#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    TOKEN_SHOW,
    TOKEN_STRING,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;

Token *get_next_token(const char *source);
void free_token(Token *token);

#endif // LEXER_H
