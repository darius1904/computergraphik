cmake_minimum_required(VERSION 3.10)

# Project name
project(AufgabenBlatt01 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings for GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Aufgabe 1 ----
add_executable(aufgabe_1
    aufgabe_1/code/01_simple_functions.cpp
)

# ---- Aufgabe 2 ----
add_executable(aufgabe_2
    aufgabe_2/code/01_stl.cpp
    aufgabe_2/code/LineStrip3D.cpp
)

# ---- Aufgabe 3 ----
add_executable(aufgabe_3
    aufgabe_3/code/01_raii.cpp
    aufgabe_3/code/MatrixInt.cpp
)

# ---- Aufgabe 4 ----
add_executable(aufgabe_4
    aufgabe_4/code/01_functions.cpp
    aufgabe_4/code/source1.cpp
    aufgabe_4/code/source2.cpp
)