#include <string>
#include <string_view>

namespace sx {
auto compile_file(std::string_view file) -> std::pmr::string;
}
