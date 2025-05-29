#pragma once

#include <string>

namespace pl {
struct source_file {
    std::string text;

    template <typename U>
    source_file(U && text)
        : text(std::forward<U>(text)) {}
};
}