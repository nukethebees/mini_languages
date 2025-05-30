#pragma once

#include <string>

namespace pl {
struct compiler_output {
    std::string text;

    template <typename U>
    compiler_output(U && text)
        : text(std::forward<U>(text)) {}
};
}