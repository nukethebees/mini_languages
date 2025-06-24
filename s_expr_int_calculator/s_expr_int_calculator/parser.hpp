#pragma once

#include <containers/span.hpp>

#include "token.hpp"
#include "s_expr.hpp"
#include "typedefs.hpp"

namespace sx {
auto parse_file(ml::span<Token> tokens) -> SExpr;
}