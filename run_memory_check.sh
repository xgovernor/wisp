#!/bin/bash
# Run memory safety checks using valgrind or AddressSanitizer (asan)
set -e

TARGET=build/wisp
SCRIPT=${1:-tests/show_test.lang}

if [ ! -f "$TARGET" ]; then
    echo "Executable $TARGET not found. Please build the project first."
    exit 1
fi

if command -v valgrind &> /dev/null; then
    echo "Running valgrind on $TARGET $SCRIPT..."
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes "$TARGET" "$SCRIPT"
else
    echo "valgrind not found. Skipping."
fi

echo "To use AddressSanitizer, rebuild with:"
echo "  CFLAGS='-fsanitize=address' CXXFLAGS='-fsanitize=address' LDFLAGS='-fsanitize=address' cmake -B build && cmake --build build"
echo "Then run:"
echo "  $TARGET $SCRIPT"
