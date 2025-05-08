// Wisp Interpreter main entry point
#define _POSIX_C_SOURCE 200809L
#define WISP_NAME "Wisp"
#define WISP_VERSION "0.2.1"
// #define WISP_AUTHOR "Abu Taher Muhammad"
#include <errno.h>
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
#include "modules/cli.h"
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

    WispCLIOptions opts;
    if (wisp_parse_cli(argc, argv, &opts) != 0)
    {
        fprintf(stderr, "Try '%s --help' for usage.\n", argv[0]);
        return 1;
    }

    if (opts.show_help)
    {
        wisp_print_help(argv[0]);
        wisp_cli_options_free(&opts);
        return 0;
    }
    if (opts.show_version)
    {
        wisp_print_version();
        wisp_cli_options_free(&opts);
        return 0;
    }

    printf("\033[36mWelcome to %s v%s.\033[0m\n", WISP_NAME, WISP_VERSION);

    struct rusage usage_start, usage_end;
    struct timespec t_start, t_end;
    if (opts.show_stats)
    {
        getrusage(RUSAGE_SELF, &usage_start);
        clock_gettime(CLOCK_MONOTONIC, &t_start);
    }

    if (!opts.script_file && !opts.command && !opts.interactive)
    {
        fprintf(stderr, "Usage: %s [options] <script> [-- [script arguments]]\n", argv[0]);
        wisp_cli_options_free(&opts);
        return 1;
    }

    // Handle -c/--command (execute code string)

    if (opts.command)
    {
        // TODO: interpret code in opts.command
        printf("[Stub] Would execute: %s\n", opts.command);
        wisp_cli_options_free(&opts);
        return 0;
    }

    // Handle -e/--eval (REPL)
    if (opts.interactive)
    {
        // TODO: launch REPL
        printf("[Stub] Would launch REPL\n");
        wisp_cli_options_free(&opts);
        return 0;
    }

    // Handle script file execution

    if (opts.script_file)
    {
        // --- Read the script file into memory safely ---
        FILE *file = fopen(opts.script_file, "r");
        if (!file)
        {
            fprintf(stderr, "Failed to open script file '%s': %s\n", opts.script_file, strerror(errno));
            wisp_cli_options_free(&opts);
            return 1;
        }
        if (fseek(file, 0, SEEK_END) != 0)
        {
            fprintf(stderr, "Failed to seek script file '%s'.\n", opts.script_file);
            fclose(file);
            wisp_cli_options_free(&opts);
            return 1;
        }
        long flen = ftell(file);
        if (flen < 0)
        {
            fprintf(stderr, "Failed to get file length for '%s'.\n", opts.script_file);
            fclose(file);
            wisp_cli_options_free(&opts);
            return 1;
        }
        rewind(file);
        char *source = malloc((size_t)flen + 1);
        if (!source)
        {
            fprintf(stderr, "Out of memory reading script file.\n");
            fclose(file);
            wisp_cli_options_free(&opts);
            return 1;
        }
        size_t nread = fread(source, 1, (size_t)flen, file);
        if (nread != (size_t)flen)
        {
            fprintf(stderr, "Failed to read script file '%s'.\n", opts.script_file);
            free(source);
            fclose(file);
            wisp_cli_options_free(&opts);
            return 1;
        }
        source[flen] = '\0';
        fclose(file);

        // --- Tokenize and interpret ---
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
    }

    if (opts.show_stats)
    {
        getrusage(RUSAGE_SELF, &usage_end);
        clock_gettime(CLOCK_MONOTONIC, &t_end);
        double elapsed = (t_end.tv_sec - t_start.tv_sec) + (t_end.tv_nsec - t_start.tv_nsec) / 1e9;
        long mem_kb = usage_end.ru_maxrss;
        printf("\033[33m[Stats] Time: %.6f sec | Max Memory: %ld KB\033[0m\n", elapsed, mem_kb);
    }
    wisp_cli_options_free(&opts);
    return 0;
}
