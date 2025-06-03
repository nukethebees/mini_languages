#pragma once

#include <string_view>

namespace intlang {
// The scanner uses a window to extract lexemes from the source code.
// We use two values:
//     An integer to represent the current position
//     A second integer to represent the end of the lexeme
// A length of zero means there are no characters in the lexeme.
class Scanner {
public:
    Scanner() = default;
    explicit Scanner(std::string_view source) : source_(source) {}

    auto source() const {
        return source_;
    }
private:
    std::string_view source_;
};
}