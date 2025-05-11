#!/bin/bash
# test_error_tester.sh - Run and check output of error_tester
set -e

BIN=./tests/error_tester

if [ ! -x "$BIN" ]; then
  echo "error_tester binary not found or not executable. Building..."
  gcc -I./src -I./src/lexer -I./src/modules -I./src/utils \
    -o tests/error_tester tests/error_tester.c \
    src/modules/logger.c src/modules/symbol_table.c src/modules/interpreter.c \
    src/utils/utils.c src/utils/error.c src/lexer/lexer.c src/utils/intern.c
fi

# Run the tester and capture output
OUTPUT=$($BIN 2>&1)

# Print output for manual inspection
printf "%s\n" "$OUTPUT"

# Simple checks for expected log lines
if echo "$OUTPUT" | grep -q "This is a test error message." && \
   echo "$OUTPUT" | grep -q "E9999" && \
   echo "$OUTPUT" | grep -q "Interpreter returned: 1"; then
  echo "[OK] error_tester produced expected output."
  exit 0
else
  echo "[FAIL] error_tester did not produce expected output." >&2
  exit 1
fi
