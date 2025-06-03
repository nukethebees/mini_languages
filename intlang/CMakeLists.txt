cmake_minimum_required (VERSION 3.28)

project ("intlang"
    LANGUAGES CXX
    VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("intlang")
add_subdirectory("tests")