#include <ostream>
#include <string>

#include "printlang/token_type.hpp"
#include "printlang/token.hpp"

namespace pl {
void PrintTo(token_type tt, std::ostream * os) {
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

void PrintTo(const token & t, std::ostream * os) {
    *os << "token{type: ";
    PrintTo(t.type, os);
    *os << ", position: " << t.position << ", length: " << t.length << "}";
}
}