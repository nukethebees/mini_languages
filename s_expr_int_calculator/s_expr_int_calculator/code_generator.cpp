#include <format>
#include <memory_resource>

#include "code_generator.hpp"

namespace sx {
auto code_generator(TokenNumber num) -> std::pmr::string {
    std::pmr::string str{std::pmr::new_delete_resource()};
    std::format_to(std::back_inserter(str), "{}\n", num);
    return str;
}
}
