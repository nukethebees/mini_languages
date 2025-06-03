add_library(intlang STATIC)

target_sources(intlang PRIVATE
    "scanner.cpp"
    "parser.cpp" 
    "ast_processor.cpp" 
    "code_generator.cpp"
 "compile_file.cpp")
target_sources(intlang PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ../
  FILES
  "ast_processor.hpp"
  "code_generator.hpp"
  "compile_file.hpp"
  "expr.hpp"
  "parse_tree.hpp"
  "parser.hpp"
  "scanner.hpp"
  "token.hpp"
)
