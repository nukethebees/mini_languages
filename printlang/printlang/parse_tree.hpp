#pragma once

#include <vector>

#include "print_stmt.hpp"

namespace ml {
struct parse_tree {
    std::vector<print_stmt> print_stmts;
};
}