# P2P-Transfer

## Description
- "P2P-Transfer" uses TCP to receive/send files from/to another peer.

## Requirements
- CMake (Version >= 3.13)
- C++-Compiler (Standard >= C++17)
- Qt (Version = 6)
- LibArchive
- GTest (Only for tests)

## Build the project

### 1. Setup
- cmake -S . -B build

### 2. Build
- All: cmake --build build
- Main-app: cmake --build build --target Main-app
- Test-app: cmake --build build --target Test-app
