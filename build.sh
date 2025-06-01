#!/bin/bash

mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug

# Run executable (adjust ./app if your target is named differently)
if [ -f bin/GameEngine ]; then
    bin/GameEngine
elif [ -f bin/GameEngine ]; then
    bin/GameEngine
else
    echo "Executable not found!"
fi

cd ..
