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

## Version Output

- `wisp -v` or `wisp --version` prints:
  ```
  v<version>
  ```
  Example:
  ```
  v0.3.7
  ```

## Command Execution

- `wisp -c '<code>'` or `wisp --command '<code>'` executes the code string directly.
- Output is minimal and industry-standard (like Python/Node.js):
  - No banners or extra lines.
  - On error, prints:
    ```
    wisp: error: failed to execute command string
    ```
    to stderr.
- Example:
  ```sh
  wisp -c 'show `Hello!`;'   # prints: Hello!
  ```

## Stats Output

- `wisp -s ...` or `wisp --stats ...` prints detailed execution stats after successful run:
  - Wall time (real elapsed time)
  - User CPU time
  - System CPU time
  - Max resident set size (memory, KB)
  - Major page faults
  - Swaps
- Output format:
  ```
  === Wisp Stats ===
    Wall time   :   0.002100 s
    User CPU    :   0.001900 s
    System CPU  :   0.000200 s
    Max RSS     :      1234 KB
    Page faults :         12
    Swaps       :          0
  ==================
  ```
- Stats are printed to stderr, not stdout.

## Help Output

- `wisp -h` or `wisp --help` prints a modern, concise help message with all options, arguments, and usage examples.

## Example Usage

```sh
wisp -v
wisp myprog.wisp
wisp -c 'show `Hello!`; let x (number) is 42; show x > 10;'
wisp -s myprog.wisp
wisp -I modules/ myprog.wisp -- arg1 arg2
```

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

For more details, see the main README or run `wisp --help`.
