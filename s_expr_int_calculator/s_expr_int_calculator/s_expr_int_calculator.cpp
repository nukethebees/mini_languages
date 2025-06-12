#include <memory_resource>

#include <containers/vector.hpp>

#include "s_expr_int_calculator.h"

int main() {
    std::pmr::vector<int> vec{std::pmr::new_delete_resource()};
    return 0;
}
