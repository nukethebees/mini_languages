#include "code_generator.hpp"
#include "compile_file.hpp"
#include "parser.hpp"

namespace pl {
auto compile_file(std::string_view file) -> error_or<compiler_output> {
    using T = error_or<compiler_output>;

    pl::parser parser(file);
    auto parse_result{parser.parse()};

    if (!parse_result) {
        return T(std::unexpect_t{}, std::move(parse_result.error()));
    }

    pl::code_generator code_gen;
    return code_gen.generate(*parse_result);
}
}
