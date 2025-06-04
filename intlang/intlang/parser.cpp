#include "parser.hpp"

namespace il {
auto Parser::parse() -> ErrorOr<ParseTree> {
    ParseTree out;

    while (!scanner_.is_eof()) {
        auto token{scanner_.scan_token()};

        switch (token.type()) {
            default:
                return std::unexpected(CompilerError(
                    "Unexpected token", CompilerErrorType::unexpected_token, token.position()));
        }
    }

    return out;
}
}
