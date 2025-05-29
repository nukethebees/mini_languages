#pragma once

#include <string_view>

#include "file_offset.hpp"
#include "file_position.hpp"

namespace pl {
class scanner {
private:
    std::string_view file;
    file_position position;
    file_offset offset;
};
}