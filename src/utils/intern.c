// intern.c - String interning utility for Wisp
#include "intern.h"
#include <stdlib.h>
#include <string.h>

#define INTERN_TABLE_SIZE 256

// Simple hash table for interning
typedef struct InternEntry
{
    char *str;
    struct InternEntry *next;
} InternEntry;

static InternEntry *intern_table[INTERN_TABLE_SIZE];

static unsigned long hash_str(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % INTERN_TABLE_SIZE;
}

const char *intern_string(const char *str)
{
    if (!str)
        return NULL;
    unsigned long h = hash_str(str);
    InternEntry *entry = intern_table[h];
    while (entry)
    {
        if (strcmp(entry->str, str) == 0)
            return entry->str;
        entry = entry->next;
    }
    // Not found, add new
    char *copy = strdup(str);
    InternEntry *new_entry = (InternEntry *)malloc(sizeof(InternEntry));
    new_entry->str = copy;
    new_entry->next = intern_table[h];
    intern_table[h] = new_entry;
    return copy;
}

void intern_cleanup(void)
{
    for (int i = 0; i < INTERN_TABLE_SIZE; ++i)
    {
        InternEntry *entry = intern_table[i];
        while (entry)
        {
            InternEntry *next = entry->next;
            free(entry->str);
            free(entry);
            entry = next;
        }
        intern_table[i] = NULL;
    }
}
