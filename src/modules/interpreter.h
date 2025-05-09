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

#endif // WISP_INTERPRETER_H
