#include "symbol_table.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/intern.h"
#include "logger.h"
#include "../utils/arena.h"

#define SYMBOL_TABLE_SIZE 211
static Variable *symbol_table[SYMBOL_TABLE_SIZE];
static Arena *symbol_arena = NULL;
#include "symbol_table.h"

static unsigned long hash_varname(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % SYMBOL_TABLE_SIZE;
}

void symbol_table_init(void)
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; ++i)
        symbol_table[i] = NULL;
    if (!symbol_arena)
        symbol_arena = arena_create();
}

void symbol_table_cleanup(void)
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; ++i)
        symbol_table[i] = NULL;
    if (symbol_arena)
    {
        arena_destroy(symbol_arena);
        symbol_arena = NULL;
    }
}

/**
 * @brief Finds a variable by name in the symbol table.
 *
 * @param name The variable name to search for.
 * @return Pointer to the Variable if found, NULL otherwise.
 */

Variable *find_variable(const char *name) {
    if (!name)
        return NULL;
    unsigned long h = hash_varname(name);
    Variable *v = symbol_table[h];
    while (v)
    {
        if (v->name == name || strcmp(v->name, name) == 0)
            return v;
        v = v->next;
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
    if (!name)
    {
        WISP_LOGE("Attempted to add variable with NULL name.");
        return;
    }
    const char *iname = intern_string(name);
    unsigned long h = hash_varname(iname);
    Variable *v = symbol_table[h];
    while (v)
    {
        if (v->name == iname || strcmp(v->name, iname) == 0)
        {
            if (v->is_constant)
            {
                WISP_LOGE("Cannot reassign to constant variable: %s", name);
                return;
            }
            // Strict type enforcement: types must match exactly
            if (strncmp(v->type, type, MAX_TYPE_LEN) != 0)
            {
                WISP_LOGE("Type error: cannot assign value of type '%s' to variable '%s' of type '%s"", type, name, v->type);
                return;
            }
            strncpy(v->value, value, MAX_VALUE_LEN - 1);
            v->value[MAX_VALUE_LEN - 1] = '\0';
            v->is_constant = is_constant;
            return;
        }
        v = v->next;
    }
    // Not found, add new
    Variable *newv = (Variable *)arena_alloc(symbol_arena, sizeof(Variable));
    newv->name = iname;
    strncpy(newv->type, type, MAX_TYPE_LEN - 1);
    newv->type[MAX_TYPE_LEN - 1] = '\0';
    strncpy(newv->value, value, MAX_VALUE_LEN - 1);
    newv->value[MAX_VALUE_LEN - 1] = '\0';
    newv->is_constant = is_constant;
    newv->next = symbol_table[h];
    symbol_table[h] = newv;
    WISP_LOGD("Allocated variable '%s' in arena", name);
}

// Expose arena for testing/inspection
const Arena *symbol_table_get_arena(void)
{
    return symbol_arena;
}
