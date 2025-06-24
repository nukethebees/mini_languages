#include <cctype>
#include <string>

#include "scanner.hpp"

#include <containers/new_delete_pmr.hpp>

namespace sx {
auto scan_file(std::string_view file) -> vec<Token> {
    vec<Token> out{ml::get_new_delete_pmr()};

    std::size_t i{0};
    std::size_t offset{0};
    std::size_t length{file.length()};

    auto get_lexeme{[&]() { return std::string_view{file.data() + i, offset}; }};
    auto get_idx{[&]() { return static_cast<FilePosition>(offset + i); }};
    auto is_eof{[&]() { return get_idx() >= length; }};
    auto get_char{[&]() {
        auto const idx{get_idx()};
        if (idx >= length) {
            return '\0';
        } else {
            return file[idx];
        }
    }};
    auto get_length{[&]() { return offset; }};
    auto is_num{[](char c) -> bool { return (c <= '9') && (c >= '0'); }};
    auto is_alpha{[](char c) -> bool { return std::isalpha(static_cast<int>(c)); }};
    auto is_idenchar{
        [](char c) -> bool { return std::isalnum(static_cast<int>(c)) || (c == '_'); }};

    while (i <= length) {
        char c{get_char()};
        switch (c) {
            case ' ':
                [[fallthrough]];
            case '\t':
                [[fallthrough]];
            case '\n': {
                ++i;
                break;
            }

            case '#': {
                ++offset;
                // Skip comments
                while ((get_char() != '\n') && !is_eof()) {
                    ++i;
                }
                break;
            }
            case '\0': {
                // End of file
                ++offset;
                out.emplace_back(i, get_length(), TokenType::END_OF_FILE, get_lexeme());
                break;
            }
            case '(': {
                ++offset;
                out.emplace_back(i, get_length(), TokenType::LEFT_PAREN, get_lexeme());
                break;
            }
            case ')': {
                ++offset;
                out.emplace_back(i, get_length(), TokenType::RIGHT_PAREN, get_lexeme());
                break;
            }
            case '+': {
                ++offset;
                out.emplace_back(i, get_length(), TokenType::PLUS, get_lexeme());
                break;
            }
            case '-': {
                ++offset;
                out.emplace_back(i, get_length(), TokenType::MINUS, get_lexeme());
                break;
            }
            default: {
                if (is_num(c)) {
                    do {
                        ++offset;
                    } while (is_num(get_char()));

                    auto lex{get_lexeme()};
                    out.emplace_back(
                        i, get_length(), TokenType::NUMBER, lex, std::stoi(std::string(lex)));
                    break;
                } else if (is_alpha(c)) {
                    do {
                        ++offset;
                    } while (is_idenchar(get_char()));
                    out.emplace_back(i, get_length(), TokenType::IDENTIFIER, get_lexeme());
                    break;
                } else {
                    offset++;
                    out.emplace_back(
                        i, get_length(), TokenType::UNEXPECTED_CHARACTER, get_lexeme());
                    break;
                }
            }
        }
        i += offset;
        offset = 0;
    }

    return out;
}
}
