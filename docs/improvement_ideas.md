# Wisp Project: Improvement Ideas and Roadmap

This document outlines possible improvements and best practices to further modernize, optimize, and professionalize the Wisp project. These suggestions are based on standard C project conventions and the current modular structure of Wisp.

---

## 1. Testing & Quality
- **Automated Unit & Integration Tests:**
  Add a `tests/unit/` directory with C unit tests (using frameworks like [Unity](http://www.throwtheswitch.org/unity), [Check](https://libcheck.github.io/check/), or [CMocka](https://cmocka.org/)) for each module. Add integration tests for CLI and interpreter.
- **Test Runner Script:**
  Add a shell script or CTest integration to run all tests automatically.
- **Continuous Integration:**
  Add GitHub Actions or GitLab CI for automatic builds and tests on push/PR.

## 2. Documentation
- **Doxygen Comments:**
  Add Doxygen-style comments to all headers and functions for auto-generated API docs.
- **Developer Guide:**
  Expand `docs/` with a CONTRIBUTING.md, module design docs, and architecture overview.
- **User Documentation:**
  Add more usage examples, advanced topics, and troubleshooting to `docs/`.

## 3. Code Quality & Safety
- **Static Analysis:**
  Integrate tools like `clang-tidy`, `cppcheck`, or `scan-build` for static code analysis.
- **Compiler Warnings:**
  Add `-Wall -Wextra -Werror` to your CMake build flags for stricter compilation.
- **Memory Safety:**
  Audit for memory leaks (use `valgrind` or `asan`), especially in the interpreter and module system.
- **Error Handling:**
  Use error codes and a central error reporting utility. Print line/column numbers and context for syntax/runtime errors.

## 4. Project Structure & Modularity
- **Interpreter Loop Modularization:**
  Move the main tokenization and execution loop into a separate function or module (e.g., `interpreter.c`/`interpreter.h`).
- **Public vs. Private Headers:**
  Move internal-only headers to a `src/` subfolder, and keep only public API headers in `include/`.
- **Namespace Prefixes:**
  Prefix all functions/types with `wisp_` or module names to avoid symbol collisions.

## 5. Performance
- **Interpreter Optimizations:**
  Profile and optimize hot paths (e.g., tokenization, symbol lookup).
- **Hash Table for Symbol Table:**
  Replace the linear search in the symbol table with a hash table for faster lookups.
- **String Interning:**
  Use string interning to reduce memory usage and speed up string comparisons.
- **Fuzz Testing:**
  Add fuzz testing for the lexer and parser.

## 6. Features & Extensibility
- **Plugin/Extension System:**
  Allow loading of native modules (shared libraries) for extending the language.
- **Configurable Import Paths:**
  Support environment variables or config files for module search paths.
- **Error Reporting:**
  Improve error messages with file/line info and context. Support colored output unless `--no-color` is set.
- **REPL:**
  Add an interactive Read-Eval-Print Loop for Wisp with line editing, history, and tab completion.
- **Standard Library:**
  Start a `stdlib/` directory for reusable Wisp modules.
- **Better Module System:**
  Support relative imports, versioning, and module metadata.

## 7. Build, Packaging & Distribution
- **Install Targets:**
  Add `make install` support in CMake for easy deployment.
- **Package Scripts:**
  Provide scripts for building `.deb`, `.rpm`, Homebrew, and Windows packages.
- **Pkg-config:**
  Provide a `wisp.pc` pkg-config file for downstream integration.

## 8. User Experience
- **Command-Line Flags:**
  Add more CLI options (e.g., `--run`, `--test`, `--strict`, etc.).
- **Error Codes:**
  Use meaningful exit codes for different error types.
- **Configuration:**
  Allow configuration via environment variables or a config file. Respect XDG Base Directory Specification on Linux.

## 9. Cross-Platform Support
- **Windows Support:**
  Test and fix any issues for Windows builds (e.g., path handling, file I/O).
- **Portable Paths:**
  Use `#ifdef` and CMake logic for OS-specific code.

## 10. Internationalization & Localization
- **i18n/l10n:**
  Prepare for internationalization by moving user-facing strings to a message catalog.

---

**Next Steps:**
- Prioritize improvements based on project goals and team needs.
- Track progress in this document or a project management tool.
- For any item, see the README or ask a maintainer for implementation guidance.
