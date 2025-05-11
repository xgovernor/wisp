# Wisp Error Log Template

This template standardizes error reporting for the Wisp language, making errors clear, actionable, and user-friendly. Use this format for all user-facing errors in the CLI, interpreter, and tools.

---

## Error Template Example

```
[Wisp Error] (E1001) UnknownFileExtension
  File:    <filename>
  Line:    <line_number> (if applicable)
  Column:  <column_number> (if applicable)

  Problem:
    Unsupported file extension '.lang' detected.

  Details:
    Only files with the '.wisp' extension are supported by the Wisp interpreter.

  Suggested Fixes:
    - Rename your file to use the '.wisp' extension.
    - Ensure you are opening the correct file type for Wisp.

  For more help, see: https://wisp-lang.org/docs/file-formats

------------------------------------------------------------
```

---

## Template Fields

- **[Wisp Error]**: Standard prefix for all errors.
- **(E####)**: Unique error code for programmatic handling and documentation.
- **Error Type**: Short, descriptive error name (e.g., `UnknownFileExtension`).
- **File/Line/Column**: Context for where the error occurred (if available).
- **Problem**: Human-readable summary of the error.
- **Details**: Additional explanation for the user.
- **Suggested Fixes**: Actionable steps to resolve the error.
- **Help Link**: URL for further documentation or help.
- **Separator**: Visual break for log readability.

---

## Usage Guidelines

- Always provide as much context as possible (file, line, column).
- Use clear, actionable language in the Problem and Suggested Fixes sections.
- Assign a unique error code for each error type.
- Link to relevant documentation for user self-service.
- Use this template for all user-facing errors in the CLI, interpreter, and tools.

---

## Example Macro for C

```c
#define WISP_ERROR_FILE_EXT(filename, ext) \
    fprintf(stderr, \
        "[Wisp Error] (E1001) UnknownFileExtension\n" \
        "  File:    %s\n" \
        "\n" \
        "  Problem:\n" \
        "    Unsupported file extension '%s' detected.\n" \
        "\n" \
        "  Details:\n" \
        "    Only files with the '.wisp' extension are supported by the Wisp interpreter.\n" \
        "\n" \
        "  Suggested Fixes:\n" \
        "    - Rename your file to use the '.wisp' extension.\n" \
        "    - Ensure you are opening the correct file type for Wisp.\n" \
        "\n" \
        "  For more help, see: https://wisp-lang.org/docs/file-formats\n" \
        "------------------------------------------------------------\n", \
        filename, ext)
```

---

## Extending the Template

For new error types, change the error code, type, and message content as needed. Keep the structure and clarity consistent for all errors.
