#pragma once

#include <cstdint>

namespace pl {
enum class token_type : uint8_t {
    comment,
    end_of_file,
    error,
    newline,
    print,
    string
};
}