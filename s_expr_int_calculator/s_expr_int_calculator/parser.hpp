#pragma once

#include <cstddef>
#include <expected>
#include <string>

#include <containers/span.hpp>

#include "s_expr.hpp"
#include "token.hpp"
#include "typedefs.hpp"

namespace sx {
struct Parser {
    std::size_t i{0};
    ml::span<Token> tokens;

    Parser(ml::span<Token> tokens)
        : tokens{tokens} {}

    auto current() -> Token { return tokens[i]; }
    void advance() { i++; }
    auto is_eof() -> bool { return i >= tokens.size(); }

    auto parse_file() -> std::expected<SExpr, std::pmr::string>;
    auto parse_expr() -> std::expected<SExpr, std::pmr::string>;
};

}
