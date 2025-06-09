#pragma once

#include <vector>
#include <string>

#include "compiler_error.hpp"

namespace il {
class CodeGenerator {
  public:
    CodeGenerator() = default;

    auto compile(std::vector<int> const& values) -> ErrorOr<std::string>;
};
}
