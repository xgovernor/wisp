# CLI Usage

## Building

From the project root:

```bash
mkdir -p build
cd build
cmake ..
make
```

## Running Scripts

```bash
./wisp ../tests/variable_test.lang
```

## CLI Flags

- `--info` Print language name, author, and version.
- `--stats` Print execution time and memory usage.
- Flags can be combined in any order:
  ```bash
  ./wisp --stats --info ../tests/variable_test.lang
  ```
