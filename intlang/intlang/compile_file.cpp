#include "compile_file.hpp"

#include "ast_processor.hpp"
#include "code_generator.hpp"
#include "parser.hpp"

#include "try_macros.hpp"

namespace il {
auto compile_file(std::string_view file) -> ErrorOr<std::string> {
    Parser parser(file);
    TRY_ASSIGN(parse_tree, parser.parse());
    AstProcessor processor;
    auto values{processor.process(*parse_tree)};
    CodeGenerator code_gen;
    return code_gen.compile(values);
}
}
