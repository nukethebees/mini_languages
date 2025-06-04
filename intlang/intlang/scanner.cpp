#include <cstdlib>

#include "scanner.hpp"

namespace il {
auto Scanner::scan_token() -> Token {
    FilePosition offset{0};

    while (true) {
        char const c{char_at(offset)};
        offset++;

        switch (c) {
            case '\0':
                goto end_of_file;
            case ' ':
                ++position_;
                offset = 0;
                break;
            case '+':
                return make_token(TokenType::plus, offset);
            case '-':
                return make_token(TokenType::minus, offset);
            case '*':
                return make_token(TokenType::star, offset);
            case '/':
                return make_token(TokenType::slash, offset);
            case ';':
                return make_token(TokenType::semicolon, offset);
            case '0':
                [[fallthrough]];
            case '1':
                [[fallthrough]];
            case '2':
                [[fallthrough]];
            case '3':
                [[fallthrough]];
            case '4':
                [[fallthrough]];
            case '5':
                [[fallthrough]];
            case '6':
                [[fallthrough]];
            case '7':
                [[fallthrough]];
            case '8':
                [[fallthrough]];
            case '9': {
                static constexpr auto is_digit{[](char c) { return c >= '0' && c <= '9'; }};

                while (is_digit(char_at(offset))) {
                    offset++;
                }

                int out{std::atoi(source_.data() + position_)};

                return make_token(TokenType::integer, offset, out);
            }
            default:
                return make_token(TokenType::error, offset);
        }
    }

end_of_file:
    return make_token(TokenType::end_of_file, offset);
}
}
