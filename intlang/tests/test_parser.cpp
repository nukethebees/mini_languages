#include <array>
#include <string_view>
#include <vector>

#include "gtest/gtest.h"

#include "intlang/compiler_error.hpp"
#include "intlang/parser.hpp"

#include "gtest_printing.hpp"

struct ParserTestInput {
    std::string_view test_name;
    std::string_view file;
    il::ErrorOr<il::ParseTree> expected_output;

    ParserTestInput(std::string_view test_name_,
                    std::string_view file_,
                    il::ErrorOr<il::ParseTree>&& exp_out)
        : test_name{test_name_}
        , file{file_}
        , expected_output{std::move(exp_out)} {}
};

class ParserTest : public testing::TestWithParam<ParserTestInput> {};

TEST_P(ParserTest, parse_file) {
    auto const& param{GetParam()};

    il::Parser parser(param.file);

// For breakpoints
#if 0
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

auto make_error(il::CompilerErrorType err) -> il::ErrorOr<il::ParseTree> {
    return std::unexpected<il::CompilerError>(il::CompilerError("", err, 0));
}

static std::vector<ParserTestInput> parser_inputs{
    {"empty_file", "", {}},
    {"semicolon", ";", {}},
    // Errors
    {"plus", "+", make_error(il::CompilerErrorType::unexpected_token)},
};
INSTANTIATE_TEST_SUITE_P(ParserTests,
                         ParserTest,
                         testing::ValuesIn(parser_inputs),
                         [](auto const& info) { return std::string(info.param.test_name); });
