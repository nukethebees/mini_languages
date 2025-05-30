#pragma once

#include <compare>
#include <vector>

#include "print_stmt.hpp"

namespace pl {
struct parse_tree {
    std::vector<print_stmt> print_stmts;

    parse_tree() = default;
    parse_tree(std::vector<print_stmt>&& stmts) noexcept
        : print_stmts(std::move(stmts)) {}

    auto operator<=>(parse_tree const& other) const noexcept = default;
};
}
