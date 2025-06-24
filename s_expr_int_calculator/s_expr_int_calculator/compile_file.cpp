#include "code_generator.hpp"
#include "compile_file.hpp"
#include "expr_processor.hpp"
#include "parser.hpp"
#include "scanner.hpp"

namespace sx {
auto compile_file(std::string_view file) -> std::pmr::string {
    auto tokens{scan_file(file)};
    auto expr{parse_file(tokens)};
    auto result{process(expr)};
    return code_generator(result);
}
}
