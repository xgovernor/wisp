

# Wisp

Wisp is a simple, strongly-typed, general-purpose programming language with a magical touch. It features template string interpolation, user-friendly CLI, and is built using Clang/LLVM.



## Features

- **Strongly Typed Variables:**
  Declare variables with explicit types (e.g., `16 bit signed number`, `10 character string`).
- **Constants:**
  Use `constant` to declare immutable values.
- **Template String Interpolation:**
  Use backtick-quoted strings with `{variable}` placeholders for easy value insertion.
- **Simple Print Statement:**
  Use `show` to print interpolated strings.
- **Code Comments:**
  Supports both `// single-line` and `/* multi-line */` comments.
- **Runtime Stats & Info:**
  CLI flags for execution time, memory usage, and language info.



## Getting Started

### Prerequisites

- CMake
- Clang
- LLVM

### Building the Project

1. Clone the repository:
   ```
   git clone <repository-url>
   cd wisp
   ```

2. Create a build directory:
   ```
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```
   cmake ..
   ```

4. Build the project:
   ```
   make
   ```

### Usage


To use Wisp, create a file with the `.lang` extension and write your code as follows:

```
show `Hello, World!`;
```

Then, run the interpreter on your source file to produce the output.

### Running Tests

To run the tests for the `show` function, execute the following command in the build directory:

```
make test
```

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
