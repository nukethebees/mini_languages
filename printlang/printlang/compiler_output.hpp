#pragma once

#include <string>
#include <string_view>

namespace pl {
struct compiler_output {
    std::string text;

    compiler_output() = default;
    template <typename U>
    compiler_output(U&& text)
        : text(std::forward<U>(text)) {}
    compiler_output(std::string_view text)
        : text(std::string(text)) {}
};
}
