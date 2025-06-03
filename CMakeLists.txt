cmake_minimum_required(VERSION 3.20)
project(GameEngine LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# On Windows with MSVC, force dynamic debug CRT
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL" CACHE STRING "" FORCE)
endif()

# Use vcpkg toolchain if VCPKG_ROOT env var is set and toolchain file not set yet
if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Find packages (prefer config-mode if available)
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

# Linux: Find OpenGL explicitly
if(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
endif()

# Sources
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    thirdparty/imgui/*.cpp
    thirdparty/glad/src/glad.c
)

add_executable(GameEngine ${SRC_FILES})

# Includes
target_include_directories(GameEngine PRIVATE
    include
    thirdparty
    thirdparty/glad/include
    thirdparty/imgui
    thirdparty/glm
    thirdparty/stb
    thirdparty/sol2
)

set_target_properties(GameEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Libraries to link
target_link_libraries(GameEngine PRIVATE
    glfw
    assimp::assimp
    Freetype::Freetype
    OpenAL::OpenAL
    BulletDynamics
    BulletCollision
    LinearMath
)

# Windows specific libs & defines
if(WIN32)
    target_compile_definitions(GameEngine PRIVATE PLATFORM_WINDOWS)
    target_link_libraries(GameEngine PRIVATE
        legacy_stdio_definitions.lib
        user32.lib
        gdi32.lib
        winmm.lib
        shell32.lib
        ole32.lib
    )
endif()

# Linux specific libs & defines
if(UNIX AND NOT APPLE)
    target_compile_definitions(GameEngine PRIVATE PLATFORM_LINUX)
    target_link_libraries(GameEngine PRIVATE
        ${OPENGL_LIBRARIES}
        pthread
        dl
    )
endif()
