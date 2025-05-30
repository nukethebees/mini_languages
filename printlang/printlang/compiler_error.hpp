#pragma once

#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <utility>

namespace pl {
enum class compiler_error_type : std::uint8_t { unknown_error = 0, not_implemented_error, unexpected_token };

class compiler_error {
  public:
    compiler_error() = default;
    template <typename U>
    compiler_error(U&& msg, compiler_error_type type)
        : msg_{std::forward<U>(msg)}
        , type_{type} {}
    compiler_error(compiler_error_type type)
        : type_{type} {}

    auto msg() const noexcept -> std::string_view { return msg_; }
    auto type() const noexcept -> compiler_error_type { return type_; }
  private:
    std::string msg_;
    compiler_error_type type_{compiler_error_type::unknown_error};
};

template <typename T>
using error_or = std::expected<T, compiler_error>;

template <typename T, typename... Args>
auto make_compile_error(Args... args) {
    if constexpr (std::is_same_v<void, T>) {
        return std::expected<void, compiler_error>(std::unexpect_t{}, compiler_error(std::forward<Args>(args)...));
    } else {
        return error_or<T>(std::unexpect_t{}, std::forward<Args>(args)...);
    }
}

}
