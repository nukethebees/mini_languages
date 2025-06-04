#pragma once

#include "compiler_error.hpp"
#include "expr.hpp"
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
    auto consume_and_discard(TokenType type) -> ErrorOr<void>;

    auto expr(std::vector<Expr>& out, Token token) -> ErrorOr<ExprIdx>;
    auto unary(Expr& out, Token token) -> ErrorOr<ExprIdx>;
    auto binary(Expr& out, Token token) -> ErrorOr<ExprIdx>;
    auto literal(Expr& out, Token token) -> ErrorOr<ExprIdx>;

    Scanner scanner_;
};
}
