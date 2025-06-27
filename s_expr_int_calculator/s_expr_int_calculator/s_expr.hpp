#pragma once

#include <containers/new_delete_pmr.hpp>

#include "typedefs.hpp"
#include "token.hpp"

namespace sx {
struct SExpr {
    Token token;
    vec<SExpr> arguments;

    SExpr(Token t, vec<SExpr> args = vec<SExpr>{ml::get_new_delete_pmr()})
        : token(t)
        , arguments(std::move(args)) {}
};
}
