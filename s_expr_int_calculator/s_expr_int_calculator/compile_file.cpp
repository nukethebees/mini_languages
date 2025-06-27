#include "code_generator.hpp"
#include "compile_file.hpp"
#include "expr_processor.hpp"
#include "parser.hpp"
#include "scanner.hpp"

namespace sx {
auto compile_file(std::string_view file) -> std::pmr::string {
    auto tokens{scan_file(file)};

    // Leave if just EOF
    if (tokens.size() == 1) {
        return "\n";
    }

    auto parser{Parser(tokens)};
    auto expr{parser.parse_file()};
    if (!expr) {
        return expr.error();
    }

    auto result{process(*expr)};
    if (!result) {
        return result.error();
    }

    return code_generator(*result);
}
}
