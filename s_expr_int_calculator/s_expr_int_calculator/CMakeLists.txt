# CMakeList.txt : CMake project for s_expr_int_calculator, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (s_expr_int_calculator "s_expr_int_calculator.cpp" "s_expr_int_calculator.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET s_expr_int_calculator PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
