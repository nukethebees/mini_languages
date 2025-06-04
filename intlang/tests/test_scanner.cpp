#include <array>
#include <string_view>
#include <vector>

#include "gtest/gtest.h"

#include "intlang/scanner.hpp"

#include "gtest_printing.hpp"

struct ScannerTestInput {
    std::string_view test_name;
    std::string_view file;
    std::vector<il::Token> exp;

    ScannerTestInput(std::string_view name,
                     std::string_view file,
                     std::vector<il::Token> exp,
                     int nth_token = 1) noexcept
        : test_name(name)
        , file(file)
        , exp(exp) {}
};

class ScannerTest : public testing::TestWithParam<ScannerTestInput> {};

TEST_P(ScannerTest, scan_single_token) {
    using namespace il;

    auto const& param{GetParam()};

// For breakpoints
#if 1
    if (param.test_name == "1") {
        auto x{0};
    }
#endif

    Scanner scan(param.file);
    std::vector<Token> out;

    while (true) {
        auto token{scan.scan_token()};
        if (token.type() == TokenType::end_of_file) {
            break;
        }
        out.push_back(token);
    }

    ASSERT_EQ(out.size(), param.exp.size());

    for (std::size_t i{0}; i < out.size(); ++i) {
        EXPECT_EQ(out[i], param.exp[i]);
    }
}

std::vector<ScannerTestInput> inputs{{
    {"eof", "", {}},
    {"space", " ", {}},
    {"one", "1", {{il::TokenType::integer, 0, 1, 1}}},
    {"twelve", "12", {{il::TokenType::integer, 0, 2, 12}}},
    {"plus", "+", {{il::TokenType::plus, 0, 1}}},
    {"minus", "-", {{il::TokenType::minus, 0, 1}}},
    {"star", "*", {{il::TokenType::star, 0, 1}}},
    {"slash", "/", {{il::TokenType::slash, 0, 1}}},
    {"semicolon", ";", {{il::TokenType::semicolon, 0, 1}}},
    {"one_plus",
     "1 +",
     {
         {il::TokenType::integer, 0, 1, 1},
         {il::TokenType::plus, 2, 1},
     }},
    {"one_plus_two_sc",
     "1 + 2;",
     {
         {il::TokenType::integer, 0, 1, 1},
         {il::TokenType::plus, 2, 1},
         {il::TokenType::integer, 4, 1, 2},
         {il::TokenType::semicolon, 5, 1},
     }},
}};
INSTANTIATE_TEST_SUITE_P(TokenScans, ScannerTest, testing::ValuesIn(inputs), [](auto const& info) {
    return std::string(info.param.test_name);
});
