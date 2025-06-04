#pragma once

#include <string_view>

#include "token.hpp"

namespace il {
class Scanner {
  public:
    Scanner() = default;
    explicit Scanner(std::string_view source)
        : source_(source) {}

    auto is_eof() const -> bool { return position_ >= source_.size(); }
    auto position() const { return position_; }
    auto scan_token() -> Token;
    auto source() const { return source_; }
  private:
    auto char_at(FilePosition offset) {
        auto const i{position_ + offset};
        return i >= source_.size() ? '\0' : source_[i];
    }
    auto make_token(TokenType type, TokenLength len, int num = 0) {
        auto const token_pos{position_};
        position_ += len;
        return Token(type, token_pos, len, num);
    }

    std::string_view source_;
    FilePosition position_{0};
};
}
