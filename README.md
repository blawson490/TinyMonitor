# TinyMonitor

A C++20 application built with CMake and Ninja.

TinyMonitor is a lightweight C++ system monitoring project.

# Release Notes
### v0.3:
 - Includes automated versioning via cmake templating
 - Centeralized automated version in CMakeLists.txt
 - Added automatic generation of version.h using CMake
 - Updated the application to display its version from the generated header file
#### v0.3.1:
 - Updated the Release notes for v0.3

### v0.2:
 - Includes hostname and uptime in hours
 - ** Online still hardcoded **

## Prerequisites

- C++20-compatible compiler
- CMake 3.21+
- Ninja

## Build

### Debug

```bash
cmake --preset debug
cmake --build --preset debug
```

### Release

```bash
cmake --preset release
cmake --build --preset release
```

## Run

```bash
./build/debug/TinyMonitor
```

## Project Structure

- `src/` — Implementation files
- `include/` — Header files
- `tests/` — Automated tests
- `docs/` — Documentation
- `scripts/` — Developer scripts

## Testing

Automated tests will be added as the project develops.

## License

No license has been selected.
