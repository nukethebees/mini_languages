#pragma once

#include <cstdint>
#include <string_view>
#include <optional>

namespace sx {
using FilePosition = uint16_t;
using TokenLength = uint8_t;
using TokenNumber = int64_t;

enum class TokenType : uint8_t { IDENTIFIER, NUMBER, ERROR };

struct Token {
    FilePosition position;
    TokenLength length;
    TokenType type;
    std::string_view lexeme;
    std::optional<TokenNumber> number_value;

    Token(FilePosition pos,
          TokenLength len,
          TokenType t,
          std::string_view lex,
          std::optional<TokenNumber> num_val = std::nullopt)
        : position(pos)
        , length(len)
        , type(t)
        , lexeme(lex)
        , number_value(num_val) {}
};
}
