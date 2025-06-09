#pragma once

#include <vector>
#include <type_traits>

#include "compiler_error.hpp"
#include "expr.hpp"
#include "parse_tree.hpp"

namespace il {
class AstProcessor {
  public:
    AstProcessor() = default;

    auto process(ParseTree const& tree) -> std::vector<int>;
    auto process(Expr const& expr) -> int;
    auto process(Expr const& expr, ExprIdx idx) -> int;
    template <typename T>
    auto process(Expr const& expr, T const& Elem) -> int {
        return 0;
    }
};
}
