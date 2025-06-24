#include "scanner.hpp"

#include <containers/new_delete_pmr.hpp>

namespace sx {
auto scan_file(std::string_view file) -> vec<Token> {
    vec<Token> out{ml::get_new_delete_pmr()};

    return out;
}
}
