#pragma once

#include <compare>
#include <cstdint>
#include <vector>

namespace il {
class LiteralExpr {
  public:
    auto operator<=>(LiteralExpr const&) const = default;
};
class UnaryExpr {
  public:
    auto operator<=>(UnaryExpr const&) const = default;
};
class BinaryExpr {
  public:
    auto operator<=>(BinaryExpr const&) const = default;
};

class ExprIdx {
  public:
    using Index = uint16_t;
    enum class Type : uint8_t { literal, unary, binary };
    ExprIdx() = default;
    constexpr ExprIdx(uint32_t index, Type type)
        : index_(index)
        , type_(type) {}

    constexpr Index index() const { return index_; }
    constexpr Type type() const { return type_; }

    constexpr auto operator<=>(ExprIdx const&) const = default;
  private:
    Index index_{0};
    Type type_{Type::literal};
};

class Expr {
  public:
    Expr() = default;

    auto operator<=>(Expr const&) const = default;
  private:
    std::vector<ExprIdx> indexes_;
    std::vector<LiteralExpr> literal_;
    std::vector<UnaryExpr> unary_;
    std::vector<BinaryExpr> binary_;
};
}
