#pragma once

#include <algorithm>
#include <array>

#include "compiler_error.hpp"
#include "expr.hpp"
#include "parse_tree.hpp"
#include "scanner.hpp"

#include "try_macros.hpp"

namespace il {
class Parser {
  public:
    enum class BinaryState { Term, Factor };

    Parser() = default;
    explicit Parser(std::string_view source)
        : scanner_(source) {}

    auto parse() -> ErrorOr<ParseTree>;
  private:
    auto consume_and_discard(TokenType type) -> ErrorOr<void>;

    auto expr(std::vector<Expr>& out, Token token) -> ErrorOr<ExprIdx>;
    auto unary(Expr& out, Token token) -> ErrorOr<ExprIdx>;
    template <BinaryState state = BinaryState::Term>
    auto binary(Expr& out, Token token) -> ErrorOr<ExprIdx> {
        TRY_ASSIGN(expr, binary_next<state>(out, token));

        static constexpr auto operators{[]() {
            if constexpr (state == BinaryState::Term) {
                return std::array<TokenType, 2>{{TokenType::plus, TokenType::minus}};
            } else {
                return std::array<TokenType, 2>{{TokenType::star, TokenType::slash}};
            }
        }()};

        auto cur_operator{scanner_.scan_token()};
        while (std::any_of(operators.cbegin(), operators.cend(), [&](auto const& elem) {
            return elem == cur_operator.type();
        })) {
            auto next_token{scanner_.scan_token()};
            TRY_ASSIGN(rhs, binary_next<state>(out, next_token));
            *expr = out.push_back(BinaryExpr(*expr, cur_operator.type(), *rhs));
            cur_operator = scanner_.scan_token();
        }
        scanner_.roll_back(cur_operator.length());

        return expr;
    }
    template <BinaryState state>
    auto binary_next(Expr& out, Token token) -> ErrorOr<ExprIdx> {
        if constexpr (state == BinaryState::Term) {
            return binary<BinaryState::Factor>(out, token);
        } else {
            return literal(out, token);
        }
    }
    auto literal(Expr& out, Token token) -> ErrorOr<ExprIdx>;

    Scanner scanner_;
};
}

#include "try_macros_undef.hpp"
