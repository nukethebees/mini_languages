#pragma once

#include <expected>
#include <string>

#include "s_expr.hpp"
#include "token.hpp"

namespace sx {
auto process(SExpr const& expr) -> std::expected<TokenNumber, std::pmr::string>;
}
