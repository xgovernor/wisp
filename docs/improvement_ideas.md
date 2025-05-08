# Wisp Project: Improvement Ideas and Roadmap

This document outlines possible improvements and best practices to further modernize, optimize, and professionalize the Wisp project. These suggestions are based on standard C project conventions and the current modular structure of Wisp.

---

## 1. Testing & Quality

- **Automated Unit Tests:**
  - Add a `tests/unit/` directory with C unit tests (using frameworks like [Unity](http://www.throwtheswitch.org/unity), [Check](https://libcheck.github.io/check/), or [CMocka](https://cmocka.org/)) for each module.
- **Test Runner Script:**
  - Add a shell script or CTest integration to run all tests automatically.

## 2. Documentation

- **Doxygen Comments:**
  - Add Doxygen-style comments to all headers and functions for auto-generated API docs.
- **Developer Guide:**
  - Expand `docs/` with a CONTRIBUTING.md and module design docs.

## 3. Code Quality & Safety

- **Static Analysis:**
  - Integrate tools like `clang-tidy`, `cppcheck`, or `scan-build` for static code analysis.
- **Compiler Warnings:**
  - Add `-Wall -Wextra -Werror` to your CMake build flags for stricter compilation.
- **Memory Safety:**
  - Audit for memory leaks (use `valgrind` or `asan`), especially in the interpreter and module system.

## 4. Project Structure

- **Public vs. Private Headers:**
  - Move internal-only headers to a `src/` subfolder, and keep only public API headers in `include/` (if you want to support library usage).
- **Namespace Prefixes:**
  - Prefix all functions/types with `wisp_` or module names to avoid symbol collisions.

## 5. Performance

- **Interpreter Optimizations:**
  - Profile and optimize hot paths (e.g., tokenization, symbol lookup).
- **Hash Table for Symbol Table:**
  - Replace the linear search in the symbol table with a hash table for faster lookups.
- **String Interning:**
  - Use string interning to reduce memory usage and speed up string comparisons.

## 6. Features & Extensibility

- **Plugin/Extension System:**
  - Allow loading of native modules (shared libraries) for extending the language.
- **Configurable Import Paths:**
  - Support environment variables or config files for module search paths.
- **Error Reporting:**
  - Improve error messages with file/line info and context.

## 7. Build & Distribution

- **Install Targets:**
  - Add `make install` support in CMake for easy deployment.
- **Package Scripts:**
  - Provide scripts for building `.deb`, `.rpm`, or Homebrew packages.
- **CI/CD Integration:**
  - Add GitHub Actions or GitLab CI for automatic builds and tests on push/PR.

## 8. Language Features

- **REPL:**
  - Add an interactive Read-Eval-Print Loop for Wisp.
- **Standard Library:**
  - Start a `stdlib/` directory for reusable Wisp modules.
- **Better Module System:**
  - Support relative imports, versioning, and module metadata.

## 9. User Experience

- **Command-Line Flags:**
  - Add more CLI options (e.g., `--version`, `--help`, `--run`, `--test`).
- **Error Codes:**
  - Use meaningful exit codes for different error types.

## 10. Cross-Platform Support

- **Windows Support:**
  - Test and fix any issues for Windows builds (e.g., path handling, file I/O).
- **Portable Paths:**
  - Use `#ifdef` and CMake logic for OS-specific code.

---

**Next Steps:**

- Prioritize improvements based on project goals and team needs.
- Track progress in this document or a project management tool.
- For any item, see the README or ask a maintainer for implementation guidance.
