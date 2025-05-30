#pragma once

#include <compare>

#include "file_position.hpp"
#include "token_type.hpp"
#include "token_length.hpp"

namespace pl {
struct token {
    token_type type;
    file_position position;
    token_length length;

    constexpr token(token_type type, file_position position, token_length length) noexcept
        : type(type), position(position), length(length) {}

    auto operator<=>(const token & other) const noexcept = default;
};
}