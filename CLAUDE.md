# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is the doctest C++ testing framework - a lightweight, fast, single-header testing framework for unit tests and TDD. This is a fork that only supports C++20 and beyond.

## Key Architecture

- **Single Header Library**: The main library is `doctest/doctest.h` - a single header that contains the entire testing framework
- **Header Assembly**: The single header is auto-generated from parts in `doctest/parts/` (doctest_fwd.h and doctest.cpp)
- **Extensions**: Additional functionality in `doctest/extensions/` including MPI support
- **Examples**: Comprehensive examples in `examples/` showing different usage patterns

## Build System

The project supports multiple build systems:

### CMake (Primary)
- Main build file: `CMakeLists.txt`
- Build with tests: `cmake -DDOCTEST_WITH_TESTS=ON`
- Build static lib with main: `cmake -DDOCTEST_WITH_MAIN_IN_STATIC_LIB=ON`

### Meson
- Build file: `meson.build`
- Simple dependency declaration for including in other projects

## Testing

Tests are primarily in `examples/all_features/` and demonstrate framework capabilities:

### Running Tests
```bash
# Build and run all tests
cmake -B build -DDOCTEST_WITH_TESTS=ON
cmake --build build
ctest --test-dir build
```

### Test Structure
- Tests use doctest macros: `TEST_CASE`, `CHECK`, `REQUIRE`, `SUBCASE`
- Test output comparison files in `examples/all_features/test_output/`
- Tests can be run with different reporters (xml, junit)

## Development

### Header Generation
- Single header is auto-generated via `scripts/cmake/assemble_single_header.cmake`
- Triggered automatically when parts are modified
- Custom target: `assemble_single_header`

### Key Components
- `doctest/parts/doctest_fwd.h` - Forward declarations
- `doctest/parts/doctest.cpp` - Main implementation  
- `doctest/extensions/` - Optional extensions (MPI, utilities)

## Configuration

Framework behavior controlled via preprocessor defines:
- `DOCTEST_CONFIG_DISABLE` - Remove all testing code
- `DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN` - Include main() function
- `DOCTEST_CONFIG_USE_STD_HEADERS` - Use standard headers

## Important Notes

- This is a C++20+ fork of the original doctest
- Tests can be written directly in production code
- Framework is designed for minimal compile-time overhead
- Thread-safe assertion support
- No global namespace pollution (everything in `doctest::`)