#include "./cli.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define WISP_VERSION "0.3.2"

static const struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'v'},
    {"stats", no_argument, 0, 's'},
    {"include", required_argument, 0, 'I'},
    {"command", required_argument, 0, 'c'},
    {"eval", no_argument, 0, 'e'},
    {"output", required_argument, 0, 'o'},
    {"no-color", no_argument, 0, 1000},
    {"strict", no_argument, 0, 1001},
    {"debug", no_argument, 0, 1002},
    {0, 0, 0, 0}};

void wisp_print_help(const char *progname)
{
    WISP_LOGS("Usage: %s [options] <script> [-- [script arguments]]", progname);
    WISP_LOGI("\nOptions:");
    WISP_LOGI("  -h, --help           Show this help message and exit");
    WISP_LOGI("  -v, --version        Show version information and exit");
    WISP_LOGI("  -s, --stats          Show execution time and memory usage");
    WISP_LOGI("  -I, --include <dir>  Add directory to module search path (can be repeated)");
    WISP_LOGI("  -c, --command <code> Execute code passed in as a string");
    WISP_LOGI("  -e, --eval           Enter interactive mode (REPL)");
    WISP_LOGI("  -o, --output <file>  Write output to file instead of stdout");
    WISP_LOGI("      --no-color       Disable colored output");
    WISP_LOGI("      --strict         Enable strict mode (fail on warnings)");
    WISP_LOGI("      --debug          Enable debug output");
    WISP_LOGI("\nArguments:");
    WISP_LOGI("  <script>             Script file to execute");
    WISP_LOGI("  --                   End of options; following are script arguments");
}

void wisp_print_version(void)
{
    printf("v%s\n", WISP_VERSION);
}

void wisp_cli_options_free(WispCLIOptions *opts)
{
    if (!opts)
        return;
    for (int i = 0; i < opts->include_dir_count; ++i)
    {
        free(opts->include_dirs[i]);
    }
    free(opts->include_dirs);
    for (int i = 0; i < opts->script_arg_count; ++i)
    {
        free(opts->script_args[i]);
    }
    free(opts->script_args);
    free(opts->output_file);
    free(opts->command);
    free(opts->script_file);
}

int wisp_parse_cli(int argc, char **argv, WispCLIOptions *opts)
{
    memset(opts, 0, sizeof(*opts));
    opts->include_dirs = NULL;
    opts->include_dir_count = 0;
    opts->script_args = NULL;
    opts->script_arg_count = 0;
    int opt, longidx;
    int parsing_options = 1;
    while (parsing_options && (opt = getopt_long(argc, argv, "hvsI:c:eo:", long_options, &longidx)) != -1)
    {
        switch (opt)
        {
        case 'h':
            opts->show_help = true;
            break;
        case 'v':
            opts->show_version = true;
            break;
        case 's':
            opts->show_stats = true;
            break;
        case 'I':
            opts->include_dirs = realloc(opts->include_dirs, sizeof(char *) * (opts->include_dir_count + 1));
            opts->include_dirs[opts->include_dir_count++] = strdup(optarg);
            break;
        case 'c':
            free(opts->command);
            opts->command = strdup(optarg);
            break;
        case 'e':
            opts->interactive = true;
            break;
        case 'o':
            free(opts->output_file);
            opts->output_file = strdup(optarg);
            break;
        case 1000:
            opts->no_color = true;
            break;
        case 1001:
            opts->strict_mode = true;
            break;
        case 1002:
            opts->debug = true;
            break;
        case '?':
            return 1; // getopt_long already prints error
        }
    }
    // Handle positional arguments and --
    if (optind < argc)
    {
        if (strcmp(argv[optind], "--") == 0)
        {
            optind++;
        }
        if (optind < argc)
        {
            opts->script_file = strdup(argv[optind++]);
        }
        // Remaining args are script arguments
        while (optind < argc)
        {
            opts->script_args = realloc(opts->script_args, sizeof(char *) * (opts->script_arg_count + 1));
            opts->script_args[opts->script_arg_count++] = strdup(argv[optind++]);
        }
    }
    return 0;
}
