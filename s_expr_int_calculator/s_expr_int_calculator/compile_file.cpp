#include "code_generator.hpp"
#include "compile_file.hpp"
#include "expr_processor.hpp"
#include "parser.hpp"
#include "scanner.hpp"

namespace sx {
auto compile_file(std::string_view file) -> std::pmr::string {
    auto tokens{scan_file(file)};
    auto parser{Parser(tokens)};
    auto expr{parser.parse_file()};
    if (!expr) {
        return expr.error();
    }

    auto result{process(*expr)};
    return code_generator(result);
}
}
