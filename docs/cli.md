# Wisp Interpreter Command-Line Interface (CLI)

The Wisp interpreter provides a production-ready, extensible command-line interface following standard conventions for language tools.

## Usage

```
wisp [options] <script> [-- [script arguments]]
```

## Options

| Short | Long         | Argument   | Description                                 |
|-------|--------------|------------|---------------------------------------------|
| `-h`  | `--help`     |            | Show this help message and exit             |
| `-v`  | `--version`  |            | Show version information and exit           |
| `-s`  | `--stats`    |            | Show execution time and memory usage        |
| `-I`  | `--include`  | `<dir>`    | Add directory to module search path         |
| `-c`  | `--command`  | `<code>`   | Execute code passed in as a string          |
| `-e`  | `--eval`     |            | Enter interactive mode (REPL)               |
| `-o`  | `--output`   | `<file>`   | Write output to file instead of stdout      |
|       | `--no-color` |            | Disable colored output                      |
|       | `--strict`   |            | Enable strict mode (fail on warnings)       |
|       | `--debug`    |            | Enable debug output                         |

## Arguments

- `<script>`: Script file to execute
- `--`: End of options; following are script arguments

## Examples

```sh
wisp --help
wisp --version
wisp -s myscript.lang
wisp -I ./lib -I ./vendor myscript.lang
wisp -c "show `Hello`"
wisp --eval
wisp myscript.lang -- arg1 arg2
```

## Implementation Notes
- Options are parsed using POSIX `getopt_long()` for robust, standard-compliant behavior.
- Multiple `-I`/`--include` options are supported.
- `--` can be used to separate interpreter options from script arguments.
- All options are documented in `src/modules/cli.h` and implemented in `src/modules/cli.c`.
