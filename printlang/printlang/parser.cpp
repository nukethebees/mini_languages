#include <utility>

#include "parser.hpp"

namespace pl {
auto parser::parse() -> error_or<parse_tree> {
    parse_tree output;

    while (!scan.is_eof()) {
        auto tkn{scan.scan_token()};

        switch (tkn.type) {
            using enum token_type;
            case newline: {
                break;
            }
            case print: {
                auto str_tkn{scan.scan_token()};
                if (str_tkn.type != token_type::string) {
                    return make_compile_error<parse_tree>("Expected string after 'print'.\n",
                                                          compiler_error_type::unexpected_token);
                }
                output.print_stmts.emplace_back(str_tkn.lexeme(scan.file()));
                consume_and_discard(token_type::newline);
                break;
            }
            default: {
                return make_compile_error<parse_tree>("Unexpected token.\n", compiler_error_type::unexpected_token);
            }
        }
    }

    return output;
}

auto parser::consume_and_discard(token_type type) -> error_or<void> {
    auto tkn{scan.scan_token()};
    if (tkn.type != type) {
        return make_compile_error<void>("Didn't get expected token.\n", compiler_error_type::unexpected_token);
    }
    return {};
}
}
