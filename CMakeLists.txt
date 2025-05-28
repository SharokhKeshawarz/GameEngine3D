cmake_minimum_required(VERSION 3.20)
project(GameEngine LANGUAGES C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

# Include directories
include_directories(
    include
    thirdparty
    thirdparty/glad/include
    thirdparty/imgui
    thirdparty/glm
    thirdparty/stb
    thirdparty/sol2
)

# Source files
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    thirdparty/imgui/*.cpp
    thirdparty/glad/src/glad.c
)

# Executable
add_executable(GameEngine ${SRC_FILES})

target_link_libraries(GameEngine PRIVATE glfw assimp::assimp Freetype::Freetype OpenAL::OpenAL BulletDynamics BulletCollision LinearMath)

# Platform-specific flags (optional but helpful)
if (WIN32)
    target_compile_definitions(GameEngine PRIVATE PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(GameEngine PRIVATE PLATFORM_MAC)
elseif(UNIX)
    target_compile_definitions(GameEngine PRIVATE PLATFORM_LINUX)
endif()

# Link system libraries if needed
if (UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(GameEngine PRIVATE ${OPENGL_LIBRARIES} dl pthread)
endif()
