#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

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

extern Variable symbol_table[MAX_VARIABLES];
extern int symbol_count;

Variable *find_variable(const char *name);
void add_variable(const char *name, const char *type, const char *value, int is_constant);

#endif // SYMBOL_TABLE_H
