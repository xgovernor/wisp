#!/bin/bash
# Run static analysis tools on the Wisp project
set -e

# Run clang-tidy if available
if command -v clang-tidy &> /dev/null; then
    echo "Running clang-tidy..."
    find src/ -name '*.c' | xargs clang-tidy --quiet || true
else
    echo "clang-tidy not found. Skipping."
fi

# Run cppcheck if available
if command -v cppcheck &> /dev/null; then
    echo "Running cppcheck..."
    cppcheck --enable=all --inconclusive --quiet --std=c11 --suppress=missingIncludeSystem src/ || true
else
    echo "cppcheck not found. Skipping."
fi

# Run scan-build if available
if command -v scan-build &> /dev/null; then
    echo "Running scan-build (CMake build)..."
    scan-build cmake -B build && scan-build cmake --build build || true
else
    echo "scan-build not found. Skipping."
fi

echo "Static analysis complete."
