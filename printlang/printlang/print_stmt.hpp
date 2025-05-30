#pragma once

#include <compare>
#include <string_view>

namespace pl {
struct print_stmt {
    std::string_view message;

    constexpr print_stmt(std::string_view msg) noexcept
        : message(msg) {}

    auto operator<=>(print_stmt const& other) const noexcept = default;
};
}
