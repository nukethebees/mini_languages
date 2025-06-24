#include <containers/new_delete_pmr.hpp>

#include "parser.hpp"

namespace sx {
auto parse_file(ml::span<Token> tokens) -> SExpr {
    return SExpr(Token{0, 0, TokenType::ERROR, "Parsing not implemented"},
                 vec<SExpr>(ml::get_new_delete_pmr()));
}
}
