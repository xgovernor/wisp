#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    // Read the source file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("Failed to open source file");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *source = malloc(length + 1);
    fread(source, 1, length, file);
    source[length] = '\0';
    fclose(file);

    // Tokenize and interpret
    Token *token = NULL;
    Token *string_token = NULL;
    int first = 1;
    while ((token = get_next_token(first ? source : NULL)) && token->type != TOKEN_EOF)
    {
        first = 0;
        if (token->type == TOKEN_SHOW)
        {
            free_token(token);
            string_token = get_next_token(NULL);
            if (string_token && string_token->type == TOKEN_STRING)
            {
                printf("%s\n", string_token->value);
                free_token(string_token);
                Token *semi_token = get_next_token(NULL);
                free_token(semi_token);
            }
            else
            {
                fprintf(stderr, "Syntax error: expected string after show\n");
                if (string_token)
                    free_token(string_token);
            }
        }
        else
        {
            free_token(token);
        }
    }
    if (token)
        free_token(token);
    free(source);
    return 0;
}
