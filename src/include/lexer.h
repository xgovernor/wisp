#ifndef LEXER_H
#define LEXER_H

/**
 * @file lexer.h
 * @brief Lexical analyzer (lexer) interface for the Wisp language.
 *
 * Declares token types, token struct, and lexer functions for tokenizing source code.
 */

/**
 * @enum TokenType
 * @brief Enumerates all possible token types in the Wisp language.
 */
typedef enum
{
    TOKEN_SHOW,       /**< 'show' keyword */
    TOKEN_LET,        /**< 'let' keyword */
    TOKEN_CONSTANT,   /**< 'constant' keyword */
    TOKEN_IS,         /**< 'is' keyword */
    TOKEN_IDENTIFIER, /**< Identifier (variable name) */
    TOKEN_TYPEDEF,    /**< Type definition in parentheses */
    TOKEN_NUMBER,     /**< Numeric literal */
    TOKEN_STRING,     /**< String literal (template or quoted) */
    TOKEN_LBRACE,     /**< '{' character */
    TOKEN_RBRACE,     /**< '}' character */
    TOKEN_SEMICOLON,  /**< ';' character */
    TOKEN_EOF,        /**< End of file/input */
    TOKEN_ERROR       /**< Error or invalid token */
} TokenType;

/**
 * @struct Token
 * @brief Represents a single token produced by the lexer.
 */
typedef struct
{
    TokenType type; /**< The type of the token */
    char *value;    /**< The string value (if applicable, else NULL) */
} Token;

/**
 * @brief Lexical analyzer: returns the next token from the source string.
 *
 * If a new source is provided, resets the lexer state to the beginning of that source.
 *
 * @param source The source string to tokenize (or NULL to continue previous).
 * @return Pointer to a dynamically allocated Token. Caller must free with free_token().
 */
Token *get_next_token(const char *source);

/**
 * @brief Frees a Token and its value.
 * @param token Pointer to the Token to free.
 */
void free_token(Token *token);

#endif // LEXER_H
