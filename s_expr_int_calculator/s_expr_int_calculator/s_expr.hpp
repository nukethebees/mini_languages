#pragma once

#include "typedefs.hpp"
#include "token.hpp"

namespace sx {
struct SExpr {
    Token token;
    vec<SExpr> arguments;

    SExpr(Token t, vec<SExpr> args = {})
        : token(t)
        , arguments(std::move(args)) {}
};
}
