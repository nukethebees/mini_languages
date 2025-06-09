#pragma once

#include <string>
#include <string_view>

#include "compiler_error.hpp"

namespace il {
auto compile_file(std::string_view file) -> ErrorOr<std::string>;
}