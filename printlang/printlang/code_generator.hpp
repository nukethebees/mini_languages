#pragma once

#include "compiler_error.hpp"
#include "compiler_output.hpp"
#include "parse_tree.hpp"

namespace pl {
class code_generator {
  public:
    code_generator() = default;

    auto generate(parse_tree const& tree) -> error_or<compiler_output>;
};
}
