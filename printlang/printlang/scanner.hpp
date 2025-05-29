#pragma once

#include <string_view>

#include "file_offset.hpp"
#include "file_position.hpp"
#include "token.hpp"

namespace pl {
class scanner {
public:
    scanner(std::string_view file)
        : file(file) {}

    auto current_char() -> char {
        if (is_eof()) {
            return '\0';
        }
        return file[position + offset];
    }
    auto is_eof() const -> bool {
        return current_position() >= file.size();
    }
    void reset() {
        position = 0;
        offset = 0;
    }
    auto scan_token() -> token;

private:
    void advance_offset_until(char c) {
        while ((current_char() != c) && !is_eof()) {
            offset++;
        }
    }
    void advance_position_to_offset() {
        position += offset;
        offset = 0;
    }
    void advance_position_beyond_offset() {
        position += offset + 1;
        offset = 0;
    }
    auto create_token(token_type type) const -> token {
        return token{type, position, offset};
    }
    auto create_end_of_file_token() const -> token {
        return create_token(token_type::end_of_file);
    }
    auto create_error_token() const -> token {
        return create_token(token_type::error);
    }
    auto current_position() const -> file_position {
        return position + offset;
    }
    auto at_least_n_chars_remaining(file_offset n) const -> bool {
        return current_position() < (file.size() - n);
    }

    std::string_view file;
    file_position position{0};
    file_offset offset{0};
};
}