#define _POSIX_C_SOURCE 200809L
/**
 * @file main.c
 * @brief Entry point for the Wisp interpreter. Handles CLI, file loading, and top-level execution loop.
 *
 * This file parses command-line arguments, loads the source file, and drives the main
 * interpretation loop using the modular lexer, symbol table, and utility functions.
 */
#include <time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#include "modules/symbol_table.h"
#include "utils/utils.h"

/**
 * @brief Main entry point for the Wisp interpreter.
 *
 * Handles CLI flags, loads the source file, and interprets the program.
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @return 0 on success, nonzero on error
 */
int main(int argc, char **argv)
{
    // Language info
    const char *LANG_NAME = "Wisp";
    const char *LANG_AUTHOR = "Abu Taher Muhammad";
    const char *LANG_VERSION = "0.1.0";
    int show_stats = 0;
    int show_info = 0;
    char *script_file = NULL;

    // Parse flags and find script filename (allow flags in any order)
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--info") == 0)
            show_info = 1;
        else if (strcmp(argv[i], "--stats") == 0)
            show_stats = 1;
        else if (!script_file && argv[i][0] != '-')
            script_file = argv[i];
    }

    if (show_info)
    {
        printf("Language: %s\nAuthor: %s\nVersion: %s\n", LANG_NAME, LANG_AUTHOR, LANG_VERSION);
        // If only --info is given, exit. If script is also given, continue to run script.
        if (!script_file)
            return 0;
    }

    printf("\033[36m%s v%s by %s\033[0m\n", LANG_NAME, LANG_VERSION, LANG_AUTHOR);

    struct rusage usage_start, usage_end;
    struct timespec t_start, t_end;
    if (show_stats)
    {
        getrusage(RUSAGE_SELF, &usage_start);
        clock_gettime(CLOCK_MONOTONIC, &t_start);
    }

    if (!script_file)
    {
        fprintf(stderr, "Usage: %s [--info] [--stats] <source_file>\n", argv[0]);
        return 1;
    }

    // Read the source file
    FILE *file = fopen(script_file, "r");
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
    int first = 1;
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
                continue;
            }
            free_token(is_token);
            Token *value_token = get_next_token(NULL);
            if (!value_token || (value_token->type != TOKEN_STRING && value_token->type != TOKEN_NUMBER && value_token->type != TOKEN_IDENTIFIER))
            {
                fprintf(stderr, "Syntax error: expected value after 'is'\n");
                if (value_token)
                    free_token(value_token);
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
            }
            continue;
        }
        free_token(token);
    }
    if (token)
        free_token(token);
    free(source);

    if (show_stats)
    {
        getrusage(RUSAGE_SELF, &usage_end);
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        double elapsed = (t_end.tv_sec - t_start.tv_sec) + (t_end.tv_nsec - t_start.tv_nsec) / 1e9;
        long mem_kb = usage_end.ru_maxrss;
        printf("\033[33m[Stats] Time: %.6f sec | Max Memory: %ld KB\033[0m\n", elapsed, mem_kb);
    }
    return 0;
}
