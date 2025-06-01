#include <format>

#include "code_generator.hpp"

namespace pl {
auto code_generator::generate(parse_tree const& tree) -> error_or<compiler_output> {
    compiler_output output;
    auto const n_stmts{tree.print_stmts.size()};

    if (!n_stmts) {
        output.text = R"(int main() {
    return 0;
}
)";
        return output;
    }

    output.text = R"(#include <array>
#include <print>
#include <string_view>

int main() {
)";
    output.text += std::format("    static constexpr std::array<std::string_view, {}> strings = {{\n", n_stmts);

    bool first{true};
    for (auto const& stmt : tree.print_stmts) {
        if (!first) {
            output.text += ",\n";
        }
        first = false;
        output.text += std::format(R"(        "{}")", stmt.message);
    }

    output.text += R"(
    };
    for (auto const& str : strings) {
        std::print("{}\n", str);
    }
    return 0;
}
)";

    return output;
}
}
