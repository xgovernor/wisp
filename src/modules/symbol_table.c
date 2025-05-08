#include "symbol_table.h"
#include <string.h>
#include <stdio.h>

Variable symbol_table[MAX_VARIABLES];
int symbol_count = 0;

/**
 * @brief Finds a variable by name in the symbol table.
 *
 * @param name The variable name to search for.
 * @return Pointer to the Variable if found, NULL otherwise.
 */
Variable *find_variable(const char *name) {
    for (int i = 0; i < symbol_count; ++i) {
        if (strcmp(symbol_table[i].name, name) == 0)
            return &symbol_table[i];
    }
    return NULL;
}

/**
 * @brief Adds a new variable or updates an existing one in the symbol table.
 *
 * If the variable already exists and is not constant, updates its value and type.
 * If it is constant, prints an error and does not update.
 *
 * @param name Variable name
 * @param type Variable type
 * @param value Variable value (as string)
 * @param is_constant 1 if constant, 0 if mutable
 */
void add_variable(const char *name, const char *type, const char *value, int is_constant) {
    Variable *v = find_variable(name);
    if (v) {
        if (v->is_constant) {
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
    if (symbol_count < MAX_VARIABLES) {
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
