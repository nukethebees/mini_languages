#pragma once

#include <string_view>

#include "file_offset.hpp"
#include "file_position.hpp"
#include "token.hpp"

namespace pl {
class scanner {
public:
    scanner(std::string_view file_)
        : file_(file_) {}

    auto current_char() -> char {
        if (is_eof()) {
            return '\0';
        }
        return file_[position + offset];
    }
    auto file() const -> std::string_view {
        return file_;
    }
    auto is_eof() const -> bool {
        return cursor_position() >= file_.size();
    }
    void reset() {
        position = 0;
        offset = 0;
    }
    auto scan_token() -> token;

private:
    // Advance offset until the current character is equal to `c` or EOF is reached
    void advance_offset_until(char c) {
        while ((current_char() != c) && !is_eof()) {
            offset++;
        }
    }
    // Move position to the current offset and reset offset to 0
    void advance_position_to_offset() {
        position += offset;
        offset = 0;
    }
    // Move position to one character beyond the current offset
    void advance_position_beyond_offset() {
        position += offset + 1;
        offset = 0;
    }
    // Check at least `n` characters remain in the file from the current cursor position
    auto at_least_n_chars_remaining(file_offset n) const -> bool {
        return cursor_position() < (file_.size() - n);
    }
    // Create a token with the current position and offset
    auto create_token(token_type type) const -> token {
        return token{type, position, offset};
    }
    auto create_end_of_file_token() const -> token {
        return create_token(token_type::end_of_file);
    }
    auto create_error_token() const -> token {
        return create_token(token_type::error);
    }
    auto cursor_position() const -> file_position {
        return position + offset;
    }
    auto previous_char() const -> char {
        return file_[cursor_position() - 1];
    }


    std::string_view file_;
    file_position position{0};
    file_offset offset{0};
};
}