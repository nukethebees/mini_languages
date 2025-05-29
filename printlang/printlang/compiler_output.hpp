#pragma once

#include <string>

namespace pl {
struct compiler_output {
    std::string text;
    bool is_error{false};

    template <typename U>
    compiler_output(U && text, bool is_error)
        : text(std::forward<U>(text))
        , is_error(is_error) {}
};
}