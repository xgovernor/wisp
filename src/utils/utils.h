#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @brief Utility functions for the Wisp interpreter.
 */

/**
 * @brief Interpolates variables in a template string using the symbol table.
 *
 * Replaces occurrences of {var} in the template with the value of var from the symbol table.
 *
 * @param template The input template string.
 * @return Pointer to a static buffer containing the interpolated string.
 */
char *interpolate(const char *template);

#endif // UTILS_H
