#pragma once

#include <containers/vector.hpp>
#include <containers/pmr_allocator.hpp>

namespace sx {
template <typename T>
using vec = ml::vector<T, ml::pmr_allocator<T>>;
}
