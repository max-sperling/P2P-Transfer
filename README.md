# P2P-Transfer

## Description
- "P2P-Transfer" uses TCP to receive/send files from/to another peer.

## Requirements
- CMake (Version >= 3.13)
- C++-Compiler (Standard >= C++17)
- Qt (Version = 6)
- GTest (Only for tests)

## Build the project

### Meta build
- cmake -S . -B build

### Actual build
- Main-app: cmake --build build --target Main-app
- Test-app: cmake --build build --target Test-app
