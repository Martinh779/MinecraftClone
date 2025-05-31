cmake_minimum_required(VERSION 3.25)
project(MinecraftClone)

set(CMAKE_CXX_STANDARD 23)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenGL REQUIRED)

# Subdirectories for external libraries
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_library(inih STATIC
        external/inih/ini.c
        external/inih/cpp/INIReader.cpp
)

target_include_directories(inih PUBLIC external/inih)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

file(GLOB_RECURSE SOURCES "Core/**/*.cpp" "Core/**/*.h")

add_compile_definitions(
        PROJECT_ROOT="${PROJECT_ROOT}"
)

add_executable(MinecraftClone
        main.cpp
        ${SOURCES}
)

target_link_libraries(MinecraftClone PRIVATE
        OpenGL::GL
        glfw
        glad
        glm
        inih
)

# Include-Pfade explizit weitergeben
target_include_directories(MinecraftClone PRIVATE
        external/glad/include
        external/inih/cpp
)
