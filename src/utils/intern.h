// intern.h - String interning utility for Wisp
#ifndef INTERN_H
#define INTERN_H

/**
 * @brief Interns a string, returning a pointer to a unique instance for each unique value.
 *        The returned pointer is valid for the lifetime of the program.
 * @param str The string to intern.
 * @return A pointer to the interned string.
 */
const char *intern_string(const char *str);

/**
 * @brief Frees all interned strings. Call at program exit if needed.
 */
void intern_cleanup(void);

#endif // INTERN_H
