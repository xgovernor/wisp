// fuzz_lexer.c - Simple fuzzing harness for the Wisp lexer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/lexer/lexer.h"

#define MAX_INPUT 4096

int main(int argc, char **argv)
{
    char buf[MAX_INPUT];
    if (argc > 1)
    {
        // Read input from file
        FILE *f = fopen(argv[1], "rb");
        if (!f)
        {
            perror("fopen");
            return 1;
        }
        size_t n = fread(buf, 1, MAX_INPUT - 1, f);
        buf[n] = '\0';
        fclose(f);
    }
    else
    {
        // Read from stdin
        size_t n = fread(buf, 1, MAX_INPUT - 1, stdin);
        buf[n] = '\0';
    }
    // Feed to lexer
    Token *tok = NULL;
    int first = 1;
    while ((tok = get_next_token(first ? buf : NULL)) && tok->type != TOKEN_EOF)
    {
        // Optionally print or check tokens
        free_token(tok);
        first = 0;
    }
    if (tok)
        free_token(tok);
    return 0;
}
