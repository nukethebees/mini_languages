#pragma once

#include <string>

#include "token.hpp"

namespace sx {
auto code_generator(TokenNumber num) -> std::pmr::string;
}