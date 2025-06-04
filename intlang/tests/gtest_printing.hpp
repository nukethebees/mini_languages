#pragma once

#include <ostream>
#include <string>

#include "intlang/token.hpp"

namespace il {
inline void PrintTo(TokenType tt, std::ostream* os) {
    std::string name{""};

    switch (tt) {
        using enum il::TokenType;
        case comment:
            name = "comment";
            break;
        case end_of_file:
            name = "end_of_file";
            break;
        case error:
            name = "error";
            break;
        case integer:
            name = "integer";
            break;
        case plus:
            name = "plus";
            break;
        case minus:
            name = "minus";
            break;
        case slash:
            name = "slash";
            break;
        case star:
            name = "star";
            break;
        default:
            name = "unknown";
            break;
    }

    *os << name;
}

inline void PrintTo(Token const& t, std::ostream* os) {
    *os << "token{type: ";
    PrintTo(t.type(), os);
    *os << ", position: " << t.position() << ", length: " << std::to_string(t.length())
        << ", num: " << std::to_string(t.num()) << "}";
}
}
