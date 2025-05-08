#ifndef WISP_CLI_H
#define WISP_CLI_H

/**
 * @file cli.h
 * @brief Command-line interface (CLI) option parsing for the Wisp interpreter.
 *
 * Provides functions and types for parsing and handling CLI options in a
 * production-ready, extensible way using standard conventions.
 */

#include <stdbool.h>

/**
 * @struct WispCLIOptions
 * @brief Stores parsed command-line options for the Wisp interpreter.
 */
typedef struct
{
    bool show_help;        /**< Show help and exit */
    bool show_version;     /**< Show version and exit */
    bool show_stats;       /**< Show execution stats */
    bool interactive;      /**< Enter REPL mode */
    bool no_color;         /**< Disable colored output */
    bool strict_mode;      /**< Enable strict mode */
    bool debug;            /**< Enable debug output */
    char *output_file;     /**< Output file path, or NULL for stdout */
    char *command;         /**< Code to execute via -c/--command */
    char **include_dirs;   /**< Array of include directories */
    int include_dir_count; /**< Number of include directories */
    char *script_file;     /**< Script file to execute */
    char **script_args;    /**< Arguments to pass to the script */
    int script_arg_count;  /**< Number of script arguments */
} WispCLIOptions;

/**
 * @brief Parse CLI options from argc/argv.
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @param opts Pointer to WispCLIOptions struct to fill
 * @return 0 on success, nonzero on error
 */
int wisp_parse_cli(int argc, char **argv, WispCLIOptions *opts);

/**
 * @brief Print the help message to stdout.
 */
void wisp_print_help(const char *progname);

/**
 * @brief Print the version message to stdout.
 */
void wisp_print_version(void);

/**
 * @brief Free any dynamically allocated memory in WispCLIOptions.
 */
void wisp_cli_options_free(WispCLIOptions *opts);

#endif // WISP_CLI_H
