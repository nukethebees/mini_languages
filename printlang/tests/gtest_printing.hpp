#pragma once

#include <ostream>
#include <string>

#include "printlang/compiler_error.hpp"
#include "printlang/parse_tree.hpp"
#include "printlang/print_stmt.hpp"
#include "printlang/token.hpp"
#include "printlang/token_type.hpp"

namespace pl {
inline void PrintTo(token_type tt, std::ostream* os) {
    std::string name{""};

    switch (tt) {
        using enum pl::token_type;
        case comment:
            name = "comment";
            break;
        case end_of_file:
            name = "end_of_file";
            break;
        case error:
            name = "error";
            break;
        case newline:
            name = "newline";
            break;
        case print:
            name = "print";
            break;
        case string:
            name = "string";
            break;
        default:
            name = "unknown";
            break;
    }

    *os << name;
}

inline void PrintTo(token const& t, std::ostream* os) {
    *os << "token{type: ";
    PrintTo(t.type, os);
    *os << ", position: " << t.position << ", length: " << t.length << "}";
}

inline void PrintTo(print_stmt const& t, std::ostream* os) {
    *os << "print_stmt{message: \"" << t.message << "\"}";
}

inline void PrintTo(parse_tree const& pt, std::ostream* os) {
    *os << "parse_tree{print_stmts: [";
    for (size_t i = 0; i < pt.print_stmts.size(); ++i) {
        if (i > 0) {
            *os << ", ";
        }
        PrintTo(pt.print_stmts[i], os);
    }
    *os << "]}";
}

inline void PrintTo(compiler_error const& ce, std::ostream* os) {
    *os << "compiler_error{msg: \"" << ce.msg() << "\", type: ";
    PrintTo(ce.type(), os);
    *os << "}";
}
}
