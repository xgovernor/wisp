
/**
 * @file symbol_table.h
 * @brief Symbol table management for Wisp interpreter.
 *
 * Provides functions and data structures for variable storage and lookup.
 */
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_VARIABLES 128
#define MAX_TYPE_LEN 64
#define MAX_NAME_LEN 64
#define MAX_VALUE_LEN 256

/**
 * @struct Variable
 * @brief Represents a variable in the Wisp symbol table.
 */

typedef struct Variable
{
    const char *name;          /**< Interned variable name */
    char type[MAX_TYPE_LEN];   /**< Variable type */
    char value[MAX_VALUE_LEN]; /**< Variable value as string */
    int is_constant;           /**< 1 if constant, 0 if mutable */
    struct Variable *next;     /**< Next in hash bucket */
} Variable;

void symbol_table_init(void);
void symbol_table_cleanup(void);

/**
 * @brief Find a variable by name in the symbol table.
 * @param name The variable name to search for.
 * @return Pointer to the Variable if found, NULL otherwise.
 */
Variable *find_variable(const char *name);

/**
 * @brief Add a new variable or update an existing one in the symbol table.
 * @param name Variable name
 * @param type Variable type
 * @param value Variable value (as string)
 * @param is_constant 1 if constant, 0 if mutable
 */
void add_variable(const char *name, const char *type, const char *value, int is_constant);

#endif // SYMBOL_TABLE_H
