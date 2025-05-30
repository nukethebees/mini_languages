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
        : type(type)
        , position(position)
        , length(length) {}

    auto lexeme(std::string_view file) -> std::string_view { return file.substr(position, length); }

    auto operator<=>(token const& other) const noexcept = default;
};
}
