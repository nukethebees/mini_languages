#include <memory_resource>

#include <containers/vector.hpp>
#include <containers/pmr_allocator.hpp>
#include <containers/new_delete_pmr.hpp>

#include "s_expr_int_calculator.h"

int main() {
    ml::vector<int, ml::pmr_allocator<int>> vec{ml::get_new_delete_pmr()};
    return 0;
}
