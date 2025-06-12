find_package(containers CONFIG REQUIRED)

add_executable (s_expr_int_calculator "s_expr_int_calculator.cpp" "s_expr_int_calculator.h")

target_link_libraries(s_expr_int_calculator PRIVATE 
    containers::containers
)