#include "code_generator.hpp"

namespace il {
auto CodeGenerator::compile(std::vector<int> const& values) -> ErrorOr<std::string> {
    std::string out;
    for (auto const& value : values) {
        out += std::to_string(value) + "\n";
    }
    return out;
}
}
