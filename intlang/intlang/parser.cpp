#include "parser.hpp"

namespace il {
auto Parser::parse() -> ErrorOr<ParseTree> {

    while (!scanner_.is_eof()) {
        auto token{scanner_.scan_token()};

        switch (token.type()) {
            default:
                return std::unexpected(CompilerError(
                    "Unexpected token", CompilerErrorType::unexpected_token, token.position()));
        }
    }

    return std::unexpected(CompilerError(
        "Not implemented", CompilerErrorType::not_implemented_error, scanner_.position()));
}
}
