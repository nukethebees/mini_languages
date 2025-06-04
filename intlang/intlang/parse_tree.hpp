#pragma once

#include <compare>
#include <vector>

#include "expr.hpp"

namespace il {
struct ParseTree {
    std::vector<Expr> exprs;

    auto operator<=>(ParseTree const &) const = default;
};
}
