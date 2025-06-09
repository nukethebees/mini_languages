#include <array>
#include <string_view>
#include <vector>

#include "gtest/gtest.h"

#include "intlang/code_generator.hpp"
#include "intlang/compile_file.hpp"

#include "gtest_printing.hpp"

struct CodeGeneratorTestInput {
    std::string_view test_name;
    std::string_view input;
    il::ErrorOr<std::string> expected_output;
    CodeGeneratorTestInput(std::string_view name,
                           std::string_view input_,
                           il::ErrorOr<std::string>&& exp_out) noexcept
        : test_name(name)
        , input(input_)
        , expected_output(std::move(exp_out)) {}
};

class CodeGeneratorTest : public testing::TestWithParam<CodeGeneratorTestInput> {};

TEST_P(CodeGeneratorTest, scan_single_token) {
    using namespace il;
    auto const& param{GetParam()};

#if 1
    if (param.test_name == "mix1") {
        auto x{0};
    }
#endif

    auto result{compile_file(param.input)};

    if (!param.expected_output) {
        ASSERT_TRUE(!result);
        EXPECT_EQ(result.error().type(), param.expected_output.error().type());
    } else {
        ASSERT_TRUE(result);
        EXPECT_EQ(result.value(), param.expected_output.value());
    }
}

std::vector<CodeGeneratorTestInput> inputs{{{"empty", "", ""},
                                            {"1_p_1", "1+1;", "2\n"},
                                            {"5_t_5", "5 * 5;", "25\n"},
                                            {"mix1",
                                             R"(
1 + 2 * 5;
)",
                                             R"(11
)"},
                                            {"mix2",
                                             R"(
1 + 2 * 5 + 1 * 3 / 5 + 6 / 7 + 91;
1 + 2 * 5 + 1 * 3 / 5 + 6 / 7 + 91;
1 + 2 * 5 + 1 * 3 / 5 + 6 / 7 + 91;
)",
                                             R"(102
102
102
)"}}};

INSTANTIATE_TEST_SUITE_P(CodeGeneratorTests,
                         CodeGeneratorTest,
                         testing::ValuesIn(inputs),
                         [](auto const& info) { return std::string(info.param.test_name); });
