#include <containers/new_delete_pmr.hpp>

#include "parser.hpp"

namespace sx {
auto Parser::parse_file() -> std::expected<SExpr, std::pmr::string> {
    auto cur{current()};

    switch (cur.type) {
        case TokenType::LEFT_PAREN: {
            advance();
            return parse_expr();
        }
        default: {
            break;
        }
    }

    return std::unexpected(std::pmr::string("Expected left paren as first token."));
}

auto Parser::parse_expr() -> std::expected<SExpr, std::pmr::string> {
    auto first_arg{current()};
    auto expr{SExpr(first_arg)};

    switch (first_arg.type) {
        using enum TokenType;
        case LEFT_PAREN: {
            return std::unexpected(std::pmr::string("First arg must be a symbol."));
        }
        case RIGHT_PAREN: {
            return std::unexpected(std::pmr::string("Expressions cannot be empty."));
        }
        case PLUS:
            [[fallthrough]];
        case MINUS: {
            advance();
            break;
        }
        default: {
            return std::unexpected(std::pmr::string("Unexpected token."));
        }
    }

    if (is_eof()) {
        return expr;
    }

    do {
        auto cur{current()};

        switch (cur.type) {
            using enum TokenType;

            case RIGHT_PAREN: {
                advance();
                goto end;
            }
            case NUMBER: {
                advance();
                expr.arguments.emplace_back(cur);
                break;
            }
            case END_OF_FILE: {
                return std::unexpected(std::pmr::string("Unexpected EOF."));
            }
            default: {
                return std::unexpected(std::pmr::string("Unexpected Token: ") +
                                       std::pmr::string(cur.lexeme));
            }
        }
    } while (true);
end:
    return std::move(expr);
}
}
