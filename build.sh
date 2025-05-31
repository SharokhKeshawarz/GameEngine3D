#!/bin/bash

# Create build directory if not exists
mkdir -p build
cd build

# Run CMake configure (change Debug to Release if needed)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
cmake --build . --config Debug

cd ..
