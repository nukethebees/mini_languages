#include <vector>

#include "gtest/gtest.h"

struct CodeGenTestInput {
    std::string_view test_name;
    std::string_view input;
    std::string_view expected_output;
};

class CodeGenTest : public testing::TestWithParam<CodeGenTestInput> {};

TEST_P(CodeGenTest, compile_file) {
    auto const& param{GetParam()};
    SUCCEED();
}

std::vector<CodeGenTestInput> const inputs{{{"empty", "", ""}}};

INSTANTIATE_TEST_SUITE_P(CodeGenTests,
                         CodeGenTest,
                         testing::ValuesIn(inputs),
                         [](auto const& info) { return std::string(info.param.test_name); });
