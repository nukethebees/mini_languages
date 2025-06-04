#include <array>
#include <string_view>
#include <vector>

#include "gtest/gtest.h"

#include "intlang/scanner.hpp"

#include "gtest_printing.hpp"

struct ParserTestInput {
    std::string_view test_name;
    std::string_view file;

    ParserTestInput(std::string_view test_name_, std::string_view file_)
        : test_name{test_name_}
        , file{file_} {}
};

class ParserTest : public testing::TestWithParam<ParserTestInput> {};

TEST_P(ParserTest, parse_file) {
    SUCCEED();
}

static std::vector<ParserTestInput> parser_inputs{
    {"empty_file", ""},
};
INSTANTIATE_TEST_SUITE_P(ParserTests,
                         ParserTest,
                         testing::ValuesIn(parser_inputs),
                         [](auto const& info) { return std::string(info.param.test_name); });
