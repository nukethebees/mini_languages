#include "parser.hpp"

namespace il {
auto Parser::parse() -> ErrorOr<ParseTree> {
    ParseTree out;

    while (!scanner_.is_eof()) {
        auto token{scanner_.scan_token()};

        switch (token.type()) {
            using enum TokenType;
            case semicolon:
                // Allow empty statements
                break;
            case integer: {
                auto result{expr(out.exprs, token)};
                if (!result) {
                    return std::unexpected(result.error());
                }
                break;
            }
            default:
                return std::unexpected(CompilerError(
                    CompilerErrorType::unexpected_token, "Unexpected token", token.position()));
        }
    }

    return out;
}

auto Parser::expr(std::vector<Expr>& out, Token token) -> ErrorOr<ExprIdx> {
    Expr expr;
    auto result{unary(expr, token)};
    if (result) {
        out.push_back(std::move(expr));
    }
    return result;
}
auto Parser::unary(Expr& out, Token token) -> ErrorOr<ExprIdx> {
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
        default:
            break;
    }

    return std::unexpected(CompilerError(CompilerErrorType::unexpected_token,
                                         "Unexpected token while parsing literal expr.",
                                         token.position()));
}
}
