#include "parser.hpp"
#include "try_macros.hpp"

namespace il {
auto Parser::parse() -> ErrorOr<ParseTree> {
    ParseTree out;

    while (!scanner_.is_eof()) {
        auto token{scanner_.scan_token()};
        if (token.type() == TokenType::semicolon) {
            continue;
        }

        TRY(expr(out.exprs, token));
        TRY(consume_and_discard(TokenType::semicolon));
    }

    return out;
}

auto Parser::consume_and_discard(TokenType type) -> ErrorOr<void> {
    auto token{scanner_.scan_token()};
    if (token.type() == type) {
        return {};
    }

    return std::unexpected(CompilerError(
        CompilerErrorType::unexpected_token, "Didn't get the expected token.\n", token.position()));
}

auto Parser::expr(std::vector<Expr>& out, Token token) -> ErrorOr<ExprIdx> {
    Expr expr;
    TRY_ASSIGN(result, unary(expr, token));
    out.push_back(std::move(expr));
    return result;
}
auto Parser::unary(Expr& out, Token token) -> ErrorOr<ExprIdx> {
    switch (token.type()) {
        using enum TokenType;
        case plus: {
            auto value_token{scanner_.scan_token()};
            TRY_ASSIGN(value_expr, unary(out, value_token));
            return out.push_back(UnaryExpr(UnaryExpr::Op::plus, *value_expr));
        }
        case minus: {
            auto value_token{scanner_.scan_token()};
            TRY_ASSIGN(value_expr, unary(out, value_token));
            return out.push_back(UnaryExpr(UnaryExpr::Op::minus, *value_expr));
        }
        default:
            break;
    }

    return binary(out, token);
}
auto Parser::binary(Expr& out, Token token) -> ErrorOr<ExprIdx> {
    return literal(out, token);
}
auto Parser::literal(Expr& out, Token token) -> ErrorOr<ExprIdx> {
    switch (token.type()) {
        using enum TokenType;
        case integer:
            return out.push_back(LiteralExpr(token.num()));
        case left_paren: {
            auto next_tkn{scanner_.scan_token()};
            TRY_ASSIGN(inner_expr, unary(out, next_tkn));
            TRY(consume_and_discard(TokenType::right_paren));
            return out.push_back(GroupingExpr(*inner_expr));
        }
        default:
            break;
    }

    return std::unexpected(CompilerError(CompilerErrorType::unexpected_token,
                                         "Unexpected token while parsing literal expr.",
                                         token.position()));
}
}
