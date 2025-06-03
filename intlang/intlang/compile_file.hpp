#pragma once

#include <string>
#include <string_view>

namespace il {
auto compile_file(std::string_view file) -> std::string;
}