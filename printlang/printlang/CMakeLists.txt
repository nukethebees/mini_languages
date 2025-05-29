add_library(printlang STATIC)

target_sources(printlang PRIVATE
    "scanner.cpp"
)
target_sources(printlang PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ../
  FILES
  "scanner.hpp"
)
