#include <string_view>

#include "gtest/gtest.h"

#include "printlang/scanner.hpp"

#include "gtest_printing.hpp"

struct ScanIO {
    std::string_view test_name;
    std::string_view file;
    pl::token exp;
    // Indicates the nth token of the string that we're checking
    int nth_token{0};

    constexpr ScanIO(std::string_view name, std::string_view file, pl::token exp) noexcept
        : test_name(name), file(file), exp(exp) {}
    constexpr ScanIO(std::string_view name, std::string_view file, pl::token exp, int nth_token) noexcept
        : test_name(name), file(file), exp(exp), nth_token(nth_token) {}
};

class ScanTokenTest : public testing::TestWithParam<ScanIO> {

};

TEST_P(ScanTokenTest, scan_single_token) {
    auto const & param{GetParam()};

    // For breakpoints
    #if 1
    if (param.test_name == "string") {
        auto x{0};
    }
    #endif

    pl::scanner scan(param.file);
    auto const n_scans{param.nth_token + 1};

    for (int i{0}; i < n_scans; i++) {
        auto token{scan.scan_token()};

        if (i == param.nth_token) {
            EXPECT_EQ(token, param.exp);
        }
    }
}

constexpr ScanIO inputs[]{
    {"eof", "", {pl::token_type::end_of_file, 0, 0}},
    {"eof_x2", "", {pl::token_type::end_of_file, 0, 0}, 1},
    {"space_eof", " ", {pl::token_type::end_of_file, 1, 0}},
    {"newline", "\n", {pl::token_type::newline, 0, 1}},
    {"newline_x2", "\n\n", {pl::token_type::newline, 1, 1}, 1},
    {"s_newline", " \n", {pl::token_type::newline, 1, 1}},
    {"print", "print", {pl::token_type::print, 0, 5}},
    {"print_s_print", "print print", {pl::token_type::print, 6, 5}, 1},
    {"s_print", " print", {pl::token_type::print, 1, 5}},
    {"string", R"("foo")", {pl::token_type::string, 1, 3}},
    {"s_string", "  \"foo\"", {pl::token_type::string, 3, 3}},
    {"string_s_string", R"("foo" "foo")", {pl::token_type::string, 7, 3}, 1},
    {"string_string", R"("foo""foo")", {pl::token_type::string, 6, 3}, 1},
    // Errors
    {"bad_identifer", "foo", {pl::token_type::error, 0, 0}},
    {"unterminated_string", R"("foo)", {pl::token_type::error, 1, 3}},
};
INSTANTIATE_TEST_SUITE_P(
    TokenScans,
    ScanTokenTest,
    testing::ValuesIn(inputs),
    [](auto const & info) {
        return std::string(info.param.test_name);
    }
);
