#include "scanner.hpp"

namespace pl {
auto scanner::scan_token() -> token {
    auto const file_length{file.size()};

    if (is_eof()) {
        return create_end_of_file_token();
    }

    while (!is_eof()) {
        char c{current_char()};
        switch (c) {
            case ' ':
                [[fallthrough]];
            case '\t':
                [[fallthrough]];
            case '\r':
                [[fallthrough]];
            case '\n':
                break;
            case '#':
            {
                advance_offset_until('\n');
                advance_position_to_offset();
                break;
            }
            case '"':
            {
                advance_position_beyond_offset();
                advance_offset_until('\n');

                if (is_eof()) {
                    return create_error_token();
                }

                auto tkn{create_token(token_type::string)};

                // Consume the closing double quote
                advance_position_beyond_offset();

                return tkn;
            }
            default:
            {
                if (c == 'p') {
                    if (!at_least_n_chars_remaining(5)) {
                        return create_error_token();
                    }

                    if (file.substr(current_position(), 5) == "print") {
                        offset += 5;
                        auto tkn{create_token(token_type::print)};
                        advance_position_to_offset();
                        return tkn;
                    }
                }
                return create_error_token();
            }
        }

        advance_position_beyond_offset();
    }

    return create_error_token();
}
}