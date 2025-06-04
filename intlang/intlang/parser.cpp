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
            }
            default:
                return std::unexpected(CompilerError(
                    CompilerErrorType::unexpected_token, "Unexpected token", token.position()));
        }
    }

    return out;
}

auto Parser::expr(std::vector<Expr>& out, Token token) -> ErrorOr<void> {
    return unary(out, token);
}
auto Parser::unary(std::vector<Expr>& out, Token token) -> ErrorOr<void> {
    return binary(out, token);
}
auto Parser::binary(std::vector<Expr>& out, Token token) -> ErrorOr<void> {
    return literal(out, token);
}
auto Parser::literal(std::vector<Expr>& out, Token token) -> ErrorOr<void> {
    switch (token.type()) {
        using enum TokenType;
        default:
            return std::unexpected(CompilerError(CompilerErrorType::unexpected_token,
                                                 "Unexpected token while parsing literal expr.",
                                                 token.position()));
    }

    return {};
}
}
