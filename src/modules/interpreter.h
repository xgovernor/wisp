#ifndef WISP_INTERPRETER_H
#define WISP_INTERPRETER_H

#include <stddef.h>
#include "lexer.h"

/**
 * @brief Run the Wisp interpreter loop on the given source code.
 *
 * @param source The source code to interpret (null-terminated string)
 * @param filename The filename for error reporting (can be NULL)
 * @return 0 on success, nonzero on error
 */
int wisp_interpret(const char *source, const char *filename);

/**
 * @brief Register an include path for module search.
 * @param path Directory path to add to the include search list.
 */
void wisp_add_include_path(const char *path);

/**
 * @brief Get the number of registered include paths.
 */
int wisp_get_include_path_count(void);

/**
 * @brief Get the include path at the given index (or NULL if out of range).
 */
const char *wisp_get_include_path(int idx);

#endif // WISP_INTERPRETER_H
