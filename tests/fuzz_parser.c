// fuzz_parser.c - Simple fuzzing harness for the Wisp parser
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/lexer/lexer.h"
#include "../src/parser/parser.h"

#define MAX_INPUT 4096

int main(int argc, char **argv)
{
    char buf[MAX_INPUT];
    if (argc > 1)
    {
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
        size_t n = fread(buf, 1, MAX_INPUT - 1, stdin);
        buf[n] = '\0';
    }
    // Feed to lexer and parser
    Token *tok = NULL;
    int first = 1;
    while ((tok = get_next_token(first ? buf : NULL)) && tok->type != TOKEN_EOF)
    {
        // Optionally pass tokens to parser here
        free_token(tok);
        first = 0;
    }
    if (tok)
        free_token(tok);
    // TODO: Actually invoke parser logic if available
    return 0;
}
