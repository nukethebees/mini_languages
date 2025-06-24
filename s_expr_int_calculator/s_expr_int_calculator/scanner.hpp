#pragma once

#include <string_view>

#include "typedefs.hpp"
#include "token.hpp"

namespace sx {
auto scan_file(std::string_view file) -> vec<Token>;
}
