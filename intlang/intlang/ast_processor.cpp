#include "ast_processor.hpp"

#include "try_macros.hpp"

namespace il {
auto AstProcessor::process(ParseTree const& tree) -> std::vector<int> {
    std::vector<int> out;
    for (auto const& expr : tree.exprs) {
        out.push_back(process(expr));
    }
    return out;
}
auto AstProcessor::process(Expr const& expr) -> int {
    return expr.empty() ? 0 : process(expr, expr.top());
}
auto AstProcessor::process(Expr const& expr, ExprIdx idx) -> int {
    switch (idx.type()) {
        using enum ExprIdx::Type;
        case literal: {
            auto const& lit{expr.get<LiteralExpr>(idx)};
            return lit.value();
        }
        case grouping: {
            auto const& group{expr.get<GroupingExpr>(idx)};
            return process(expr, group.expr());
        }
        case unary: {
            auto const& unary{expr.get<UnaryExpr>(idx)};
            auto const value{process(expr, unary.expr())};
            if (unary.op() == UnaryExpr::Op::plus) {
                return value;
            } else if (unary.op() == UnaryExpr::Op::minus) {
                return -value;
            }
            break;
        }
        case binary: {
            auto const& bin{expr.get<BinaryExpr>(idx)};
            auto const lhs{process(expr, bin.lhs())};
            auto const rhs{process(expr, bin.rhs())};
            switch (bin.op()) {
                using enum TokenType;
                case plus:
                    return lhs + rhs;
                case minus:
                    return lhs - rhs;
                case star:
                    return lhs * rhs;
                case slash:
                    return lhs / rhs;
                default:
                    throw CompilerError(CompilerErrorType::not_implemented_error,
                                        "Binary operator not implemented.",
                                        0);
            }
            break;
        }
    }

    return std::numeric_limits<int>::min();
}
}
