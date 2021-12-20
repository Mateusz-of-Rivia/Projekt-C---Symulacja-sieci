cmake_minimum_required(VERSION 3.17)
project(untitled5)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wunused-value -Wsign-compare)
set(CMAKE_CXX_STANDARD 20)
include_directories(include)
set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        )
add_executable(untitled5 main.cpp)