add_library(printlang STATIC)

target_sources(printlang PRIVATE
    "scanner.cpp"
 "parser.cpp")
target_sources(printlang PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ../
  FILES
  "code_generator.hpp"
  "compiler_output.hpp"
  "file_offset.hpp"
  "file_position.hpp"
  "parser.hpp"
  "parse_tree.hpp"
  "print_stmt.hpp"
  "scanner.hpp"
  "source_file.hpp"
  "token.hpp"
  "token_length.hpp"
  "token_type.hpp"
)
