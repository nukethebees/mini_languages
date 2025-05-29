#pragma once

#include <string_view>

#include "scanner.hpp"

namespace pl {
class parser {
public:
    parser(std::string_view file)
        : scan(file) {}

private:
    scanner scan{file};
};
}