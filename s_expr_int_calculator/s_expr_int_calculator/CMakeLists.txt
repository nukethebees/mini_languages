find_package(containers CONFIG REQUIRED)

add_library(s_expr_int_calculator STATIC)
target_sources(s_expr_int_calculator PRIVATE
    "scanner.cpp" 
    "parser.cpp" 
    "expr_processor.cpp"
 "code_generator.cpp" "compile_file.cpp")
target_sources(s_expr_int_calculator PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ../
  FILES
  "scanner.hpp"
)
target_link_libraries(s_expr_int_calculator PRIVATE 
    containers::containers
)