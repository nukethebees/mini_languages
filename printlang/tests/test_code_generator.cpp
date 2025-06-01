#include <array>

#include "gtest/gtest.h"

#include "printlang/code_generator.hpp"
#include "printlang/compile_file.hpp"
#include "printlang/parser.hpp"

struct CodeGenTestInput {
    std::string_view test_name;
    std::string_view input;
    std::string_view expected_output;
};

class CodeGenTest : public testing::TestWithParam<CodeGenTestInput> {};

TEST_P(CodeGenTest, compile_file) {
    auto const& param{GetParam()};

    auto output{pl::compile_file(param.input)};
    ASSERT_TRUE(output);
    std::string_view got{output.value().text};

    EXPECT_EQ(got, param.expected_output) << "\nGot:\n" << got << "\nExpected:\n" << param.expected_output;
}

std::array<CodeGenTestInput, 3> const inputs{{{"empty_file", "", "int main() {\n    return 0;\n}\n"},
                                              {"single_print",
                                               R"(
print "foo"
)",
                                               R"(#include <array>
#include <print>
#include <string_view>

int main() {
    static constexpr std::array<std::string_view, 1> strings = {
        "foo"
    };
    for (auto const& str : strings) {
        std::print("{}\n", str);
    }
    return 0;
}
)"},
                                              {"two_prints",
                                               R"(
print "foo"
# A comment
print "bar"
)",
                                               R"(#include <array>
#include <print>
#include <string_view>

int main() {
    static constexpr std::array<std::string_view, 2> strings = {
        "foo",
        "bar"
    };
    for (auto const& str : strings) {
        std::print("{}\n", str);
    }
    return 0;
}
)"}}};

INSTANTIATE_TEST_SUITE_P(CodeGenTests, CodeGenTest, testing::ValuesIn(inputs), [](auto const& info) {
    return std::string(info.param.test_name);
});
