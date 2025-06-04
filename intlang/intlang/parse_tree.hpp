#pragma once

#include <compare>
#include <vector>

#include "expr.hpp"

namespace il {
struct ParseTree {
    std::vector<Expr> exprs;

    ParseTree() = default;
    ParseTree(std::vector<Expr>&& exprs)
        : exprs{std::move(exprs)} {}

    auto operator<=>(ParseTree const&) const = default;
};
}
