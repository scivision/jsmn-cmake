# jsmn-cmake

use JSMN C library for JSON parsing in CMake projects for C embedded systems.

## Example

Build program. This auto-downloads the C header library JSMN.

```sh
cmake -B build
cmake --build build
```

optionally, run test

```sh
ctest --test-dir build
```
