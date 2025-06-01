#pragma once

#include <string_view>

#include "compiler_error.hpp"
#include "compiler_output.hpp"

namespace pl {
auto compile_file(std::string_view file) -> error_or<compiler_output>;
}
