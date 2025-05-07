# Extending Wisp

Wisp is designed for easy extension. To add new types, statements, or features:

1. **Lexer:**
   - Update `src/lexer.c` and `src/include/lexer.h` to recognize new tokens.
2. **Parser/Interpreter:**
   - Update `src/main.c` and/or `src/parser.c` to handle new syntax or features.
3. **Testing:**
   - Add new test scripts in `tests/` to cover new features.
4. **Documentation:**
   - Update docs in `docs/` to reflect changes.

For major changes, follow the existing code style and structure for consistency.
