#include "expr_processor.hpp"

namespace sx {
auto process(SExpr const& expr) -> std::expected<TokenNumber, std::pmr::string> {
    TokenNumber num{0};

    switch (expr.token.type) {
        case TokenType::NUMBER: {
            return *expr.token.number_value;
        }
        case TokenType::PLUS: {
            for (auto const& arg : expr.arguments) {
                auto res{process(arg)};
                if (!res) {
                    return res;
                }
                num += *res;
            }
            break;
        }
        case TokenType::MINUS: {
            bool first{true};
            for (auto const& arg : expr.arguments) {
                auto res{process(arg)};
                if (!res) {
                    return res;
                }
                if (first) {
                    num = *res;
                    first = false;
                } else {
                    num -= *res;
                }
            }
            break;
        }
        default: {
            return std::unexpected("Unexpected token while processing expression.\n");
        }
    }

    return num;
}
}
