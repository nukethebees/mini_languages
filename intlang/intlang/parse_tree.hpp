#pragma once

#include <vector>

#include "expr.hpp"

namespace il {
struct ParseTree {
    std::vector<Expr> exprs;
};
}