#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define MAX_VARIABLES 128
#define MAX_TYPE_LEN 64
#define MAX_NAME_LEN 64
#define MAX_VALUE_LEN 256

typedef struct
{
    char name[MAX_NAME_LEN];
    char type[MAX_TYPE_LEN];
    char value[MAX_VALUE_LEN];
    int is_constant;
} Variable;

Variable symbol_table[MAX_VARIABLES];
int symbol_count = 0;

Variable *find_variable(const char *name)
{
    for (int i = 0; i < symbol_count; ++i)
    {
        if (strcmp(symbol_table[i].name, name) == 0)
            return &symbol_table[i];
    }
    return NULL;
}

void add_variable(const char *name, const char *type, const char *value, int is_constant)
{
    Variable *v = find_variable(name);
    if (v)
    {
        if (v->is_constant)
        {
            fprintf(stderr, "\033[31mCannot reassign to constant variable: %s\033[0m\n", name);
            return;
        }
        strncpy(v->type, type, MAX_TYPE_LEN - 1);
        v->type[MAX_TYPE_LEN - 1] = '\0';
        strncpy(v->value, value, MAX_VALUE_LEN - 1);
        v->value[MAX_VALUE_LEN - 1] = '\0';
        v->is_constant = is_constant;
        return;
    }
    if (symbol_count < MAX_VARIABLES)
    {
        strncpy(symbol_table[symbol_count].name, name, MAX_NAME_LEN - 1);
        symbol_table[symbol_count].name[MAX_NAME_LEN - 1] = '\0';
        strncpy(symbol_table[symbol_count].type, type, MAX_TYPE_LEN - 1);
        symbol_table[symbol_count].type[MAX_TYPE_LEN - 1] = '\0';
        strncpy(symbol_table[symbol_count].value, value, MAX_VALUE_LEN - 1);
        symbol_table[symbol_count].value[MAX_VALUE_LEN - 1] = '\0';
        symbol_table[symbol_count].is_constant = is_constant;
        symbol_count++;
    }
}

char *interpolate(const char *template)
{
    static char buffer[512];
    int bufpos = 0;
    for (int i = 0; template[i] != '\0' && bufpos < 511;)
    {
        if (template[i] == '{')
        {
            int j = i + 1;
            char varname[MAX_NAME_LEN] = {0};
            int k = 0;
            while (template[j] != '}' && template[j] != '\0' && k < MAX_NAME_LEN - 1)
            {
                varname[k++] = template[j++];
            }
            varname[k] = '\0';
            if (template[j] == '}')
            {
                Variable *v = find_variable(varname);
                if (v)
                {
                    int l = 0;
                    while (v->value[l] != '\0' && bufpos < 511)
                        buffer[bufpos++] = v->value[l++];
                }
                i = j + 1;
                continue;
            }
        }
        buffer[bufpos++] = template[i++];
    }
    buffer[bufpos] = '\0';
    return buffer;
}

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
    return 0;
}
