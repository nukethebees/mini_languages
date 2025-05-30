#pragma once

#include <string_view>

#include "compiler_error.hpp"
#include "parse_tree.hpp"
#include "scanner.hpp"
#include "token_type.hpp"

namespace pl {
class parser {
  public:
    parser(std::string_view file)
        : scan(file) {}

    auto parse() -> error_or<parse_tree>;
  private:
    auto consume_and_discard(token_type type) -> error_or<void>;

    scanner scan;
};
}
