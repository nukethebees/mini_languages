#pragma once

#include <compare>
#include <cstddef>
#include <cstdint>

namespace il {
using FilePosition = uint16_t;
using TokenLength = uint8_t;

enum class TokenType : uint8_t {
    comment,
    end_of_file,
    error,
    identifier,
    integer,
    minus,
    plus,
    semicolon,
    slash,
    star
};

class Token {
  public:
    Token() = default;
    constexpr Token(TokenType type, FilePosition position, TokenLength length, int num = 0)
        : position_(position)
        , length_(length)
        , type_(type)
        , num_(num) {}

    // Accessors
    constexpr auto position() const { return position_; }
    constexpr auto length() const { return length_; }
    constexpr auto type() const { return type_; }
    constexpr auto num() const { return num_; }

    auto operator<=>(Token const&) const = default;
  private:
    FilePosition position_{0};
    TokenLength length_{0};
    TokenType type_{TokenType::error};
    int num_{0};
};
}
