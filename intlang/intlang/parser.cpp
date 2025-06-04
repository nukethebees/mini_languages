#include "parser.hpp"

namespace il {
auto Parser::parse() -> ErrorOr<ParseTree> {
    return std::unexpected(CompilerError(
        "Not implemented", CompilerErrorType::not_implemented_error, scanner_.position()));
}
}
