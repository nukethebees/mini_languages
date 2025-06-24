#pragma once 

#include "s_expr.hpp"
#include "token.hpp"

namespace sx {
auto process(SExpr const & expr) -> TokenNumber;
}