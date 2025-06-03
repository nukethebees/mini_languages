#pragma once

#include <cstddef>
#include <cstdint>

namespace il {
using FilePosition = uint16_t;
using TokenLength = uint8_t;

enum class TokenType : uint8_t {
    literal,
    identifier,
    error
};

class Token {
public:
    Token() = default;
    constexpr Token(FilePosition position, TokenLength length, TokenType type)
        : position_(position), length_(length), type_(type) {}
private:
    FilePosition position_{0};
    TokenLength length_{0};
    TokenType type_{TokenType::error};
};
}