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
    auto expr(std::vector<Expr>& out, Token token) -> ErrorOr<void>;
    auto unary(std::vector<Expr>& out, Token token) -> ErrorOr<void>;
    auto binary(std::vector<Expr>& out, Token token) -> ErrorOr<void>;
    auto literal(std::vector<Expr>& out, Token token) -> ErrorOr<void>;
  private:
    Scanner scanner_;
};
}
