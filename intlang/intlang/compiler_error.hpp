#pragma once

#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <utility>

#include "token.hpp"

namespace il {
enum class CompilerErrorType : std::uint8_t {
    unknown_error = 0,
    not_implemented_error,
    unexpected_token
};

class CompilerError {
  public:
    CompilerError() = default;
    CompilerError(std::string_view msg, CompilerErrorType type, FilePosition pos)
        : msg_{msg}
        , type_{type}
        , position_{pos} {}

    auto msg() const noexcept -> std::string_view { return msg_; }
    auto type() const noexcept -> CompilerErrorType { return type_; }
    auto position() const noexcept -> FilePosition { return position_; }
  private:
    std::string_view msg_{""};
    CompilerErrorType type_{CompilerErrorType::unknown_error};
    FilePosition position_{0};
};

template <typename T>
using ErrorOr = std::expected<T, CompilerError>;
}
