#pragma once

#include "file_position.hpp"
#include "token_type.hpp"
#include "token_length.hpp"

namespace pl {
struct token {
    token_type type;
    file_position position;
    token_length length;
};
}