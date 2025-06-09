#pragma once

#include <compare>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "token.hpp"

namespace il {
class ExprIdx {
  public:
    using Index = uint16_t;
    enum class Type : uint8_t { literal, grouping, unary, binary };
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

class LiteralExpr {
  public:
    LiteralExpr() = delete;
    LiteralExpr(int value)
        : value_{value} {}

    auto value() const { return value_; }

    auto operator<=>(LiteralExpr const&) const = default;
  private:
    int value_;
};
class GroupingExpr {
  public:
    GroupingExpr(ExprIdx expr)
        : expr_{expr} {}

    auto expr() const { return expr_; }

    auto operator<=>(GroupingExpr const&) const = default;
  private:
    ExprIdx expr_;
};
class UnaryExpr {
  public:
    enum class Op : uint8_t { plus, minus };

    UnaryExpr(Op op, ExprIdx expr)
        : op_{op}
        , expr_{expr} {}

    auto op() const { return op_; }
    auto expr() const { return expr_; }

    auto operator<=>(UnaryExpr const&) const = default;
  private:
    Op op_;
    ExprIdx expr_;
};
class BinaryExpr {
  public:
    BinaryExpr(ExprIdx lhs, TokenType op, ExprIdx rhs)
        : op_{op}
        , lhs_{lhs}
        , rhs_{rhs} {}

    auto op() const { return op_; }
    auto lhs() const { return lhs_; }
    auto rhs() const { return rhs_; }

    auto operator<=>(BinaryExpr const&) const = default;
  private:
    TokenType op_;
    ExprIdx lhs_;
    ExprIdx rhs_;
};

class Expr {
  public:
    Expr() = default;

    template <typename U>
    auto push_back(U&& elem) -> ExprIdx {
        using UU = std::remove_cvref_t<U>;

        if constexpr (std::is_same_v<UU, LiteralExpr>) {
            return add_elem<ExprIdx::Type::literal>(literal_, std::move(elem));
        } else if constexpr (std::is_same_v<UU, GroupingExpr>) {
            return add_elem<ExprIdx::Type::grouping>(group_, std::move(elem));
        } else if constexpr (std::is_same_v<UU, UnaryExpr>) {
            return add_elem<ExprIdx::Type::unary>(unary_, std::move(elem));
        } else if constexpr (std::is_same_v<UU, BinaryExpr>) {
            return add_elem<ExprIdx::Type::binary>(binary_, std::move(elem));
        } else {
            static_assert(!sizeof(UU), "Missing branch.\n");
        }
    }
    template <typename U, typename Self>
    auto get(this Self&& self, ExprIdx idx) -> auto&& {
        using UU = std::remove_cvref_t<U>;
        if constexpr (std::is_same_v<UU, LiteralExpr>) {
            return std::forward<Self>(self).literal_[idx.index()];
        } else if constexpr (std::is_same_v<UU, GroupingExpr>) {
            return std::forward<Self>(self).group_[idx.index()];
        } else if constexpr (std::is_same_v<UU, UnaryExpr>) {
            return std::forward<Self>(self).unary_[idx.index()];
        } else if constexpr (std::is_same_v<UU, BinaryExpr>) {
            return std::forward<Self>(self).binary_[idx.index()];
        } else {
            static_assert(!sizeof(UU), "Missing branch.\n");
        }
    }

    auto empty() const -> bool { return index_.empty(); }
    auto size() const -> std::size_t { return index_.size(); }
    auto indexes() const -> std::vector<ExprIdx> const& { return index_; }
    auto top() const -> ExprIdx {
        if (index_.empty()) {
            return ExprIdx(0, ExprIdx::Type::literal);
        }
        return index_.back();
    }

    auto operator<=>(Expr const&) const = default;
  private:
    template <ExprIdx::Type type>
    auto add_elem(auto& collection, auto&& value) {
        collection.push_back(std::forward<decltype(value)>(value));
        auto const idx{collection.size() - 1};
        auto const expr_idx{ExprIdx(idx, type)};
        index_.push_back(expr_idx);
        return expr_idx;
    }

    std::vector<ExprIdx> index_;
    std::vector<GroupingExpr> group_;
    std::vector<LiteralExpr> literal_;
    std::vector<UnaryExpr> unary_;
    std::vector<BinaryExpr> binary_;
};
}
