cmake_minimum_required (VERSION 3.28)

project ("printlang"
    LANGUAGES CXX
    VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("printlang")
add_subdirectory("tests")