# Wisp CLI Implementation Notes: Output Redirection (`-o` / `--output`)

## Overview

The Wisp interpreter supports output redirection via the `-o <file>` or `--output <file>` command-line option. This feature allows users to direct all standard output (stdout) from script execution or command evaluation to a specified file, rather than the terminal.

## Implementation Details

- **Location:** Output redirection is implemented in `src/main.c`.
- **When Used:** If the user provides the `-o` or `--output` option, the interpreter attempts to open the specified file for writing before executing any script or command.
- **Mechanism:**
  - The interpreter saves the current `stdout` stream.
  - It then redirects `stdout` to the opened file using the C standard library.
  - All output produced by the script (e.g., via `print` statements or C `printf`) is written to the output file.
  - After execution, the interpreter flushes the output, restores the original `stdout`, and closes the file.
- **Error Handling:**
  - If the file cannot be opened, an error is printed to `stderr` and execution aborts.
  - If an error occurs during execution, the interpreter ensures that `stdout` is restored and the file is closed before exiting.
- **Scope:** Only `stdout` is redirected. Errors and statistics are always printed to `stderr` for visibility.

## Example Usage

```sh
wisp -o result.txt myscript.wisp
wisp --output=output.log -c "(print 42)"
```

## Code Excerpt

```c
// Handle output redirection if -o/--output is given
FILE *original_stdout = NULL;
FILE *output_file_handle = NULL;
if (opts.output_file)
{
    output_file_handle = fopen(opts.output_file, "w");
    if (!output_file_handle)
    {
        fprintf(stderr, "wisp: error: could not open output file '%s'\n", opts.output_file);
        // ...cleanup and return...
    }
    original_stdout = stdout;
    fflush(stdout);
    stdout = output_file_handle;
}
// ...execute script or command...
if (output_file_handle)
{
    fflush(stdout);
    stdout = original_stdout;
    fclose(output_file_handle);
}
```

## Summary

This approach ensures robust, user-friendly output redirection for all Wisp CLI workflows, matching industry standards and providing clear error handling and resource management.
