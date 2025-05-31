@echo off
REM Create build directory if it doesn't exist
if not exist build (
    mkdir build
)

cd build

REM Configure with CMake (Debug build)
cmake -DCMAKE_BUILD_TYPE=Debug ..

REM Build the project
cmake --build . --config Debug

REM Run the executable
if exist bin\Debug\GameEngine.exe (
    bin\Debug\GameEngine.exe
) else if exist GameEngine.exe (
    GameEngine.exe
) else (
    echo Executable not found!
)

cd ..
pause
