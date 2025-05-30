#include <array>
#include <string_view>
#include <variant>

#include "gtest/gtest.h"

#include "printlang/parser.hpp"
#include "printlang/parse_tree.hpp"
#include "printlang/compiler_error.hpp"

#include "gtest_printing.hpp"

using namespace std::literals::string_view_literals;

using expected_result_t = pl::error_or<pl::parse_tree>;
using et = pl::compiler_error_type;
using print_stmts = std::vector<pl::print_stmt>;

template <typename... Args>
auto make_parse_error(Args... args) {
    return pl::make_compile_error<pl::parse_tree>(std::forward<Args>(args)...);
}

struct ParseTestInput {
    std::string_view test_name;
    std::string_view input;
    expected_result_t expected_output;

    template <typename ResT>
    ParseTestInput(std::string_view name, std::string_view input, ResT&& expected) noexcept
        : test_name(name)
        , input(input)
        , expected_output(std::forward<ResT>(expected)) {}
};

class ParseFileTest : public testing::TestWithParam<ParseTestInput> {};

TEST_P(ParseFileTest, parse_file) {
    auto const& param{GetParam()};
    pl::parser parser(param.input);

// For breakpoints
#if 1
    if (param.test_name == "print_foo") {
        auto x{0};
    }
#endif

    auto result{parser.parse()};

    if (!param.expected_output) {
        ASSERT_TRUE(!result);
        EXPECT_EQ(result.error().type(), param.expected_output.error().type());
    } else {
        ASSERT_TRUE(result);
        EXPECT_EQ(result.value(), param.expected_output.value());
    }
}

std::array<ParseTestInput, 6> const inputs{{
    // Passes
    {"empty_file", "", pl::parse_tree()},
    {"newlines", "\n\n\n", pl::parse_tree()},
    {"print_foo", R"(print "foo")", pl::parse_tree(print_stmts{{"foo"sv}})},
    {"print_3",
     R"(
print "foo"
print "bar"
print "baz"
)",
     pl::parse_tree(print_stmts{
         {"foo"sv},
         {"bar"sv},
         {"baz"sv},
     })},
    {"print_with_comments",
     R"(
# This is a comment
print "foo"
# So is this
print "bar"
print "baz" # so is this
)",
     pl::parse_tree(print_stmts{
         {"foo"sv},
         {"bar"sv},
         {"baz"sv},
     })},
    // Fails
    {"plus_token", "+", make_parse_error(et::unexpected_token)},
}};
INSTANTIATE_TEST_SUITE_P(ParseTests, ParseFileTest, testing::ValuesIn(inputs), [](auto const& info) {
    return std::string(info.param.test_name);
});
