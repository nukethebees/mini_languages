find_package(containers CONFIG REQUIRED)

add_library(s_expr_int_calculator STATIC)
target_sources(s_expr_int_calculator PRIVATE
    "s_expr_int_calculator.cpp"
)
target_sources(s_expr_int_calculator PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ../
  FILES
  "s_expr_int_calculator.hpp"
)
target_link_libraries(s_expr_int_calculator PRIVATE 
    containers::containers
)