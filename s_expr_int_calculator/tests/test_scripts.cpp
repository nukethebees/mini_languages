#include <vector>

#include "gtest/gtest.h"

#include "../s_expr_int_calculator/compile_file.hpp"

struct CodeGenTestInput {
    std::string_view test_name;
    std::string_view input;
    std::string_view expected_output;
};

class CodeGenTest : public testing::TestWithParam<CodeGenTestInput> {};

TEST_P(CodeGenTest, compile_file) {
    auto const& param{GetParam()};
    auto out{sx::compile_file(param.input)};
    EXPECT_EQ(out, param.expected_output)
        << "Test: " << param.test_name << "\nInput: " << param.input
        << "\nExpected Output: " << param.expected_output << "\nActual Output: " << out;
}

std::vector<CodeGenTestInput> const inputs{{{"empty", "", ""}}};

INSTANTIATE_TEST_SUITE_P(CodeGenTests,
                         CodeGenTest,
                         testing::ValuesIn(inputs),
                         [](auto const& info) { return std::string(info.param.test_name); });
