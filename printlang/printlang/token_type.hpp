#pragma once

#include <cstdint>

namespace pl {
enum class token_type : uint8_t {
    error,
    print,
    string,
    newline
};
}