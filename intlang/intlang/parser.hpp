#pragma once

#include "compiler_error.hpp"
#include "parse_tree.hpp"
#include "scanner.hpp"

namespace il {
class Parser {
  public:
    Parser() = default;
    explicit Parser(std::string_view source)
        : scanner_(source) {}

    auto parse() -> ErrorOr<ParseTree>;
  private:
    Scanner scanner_;
};
}
