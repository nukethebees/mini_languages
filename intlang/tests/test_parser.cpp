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
#if 1
    if (param.test_name == "one_plus_two_times_three") {
        auto x{0};
    }
#endif

    auto result{parser.parse()};

    if (!param.expected_output) {
        ASSERT_TRUE(!result);
        EXPECT_EQ(result.error().type(), param.expected_output.error().type());
    } else {
        ASSERT_TRUE(result);
        auto const& out{result.value()};
        auto const& exp{param.expected_output.value()};

        EXPECT_EQ(out, exp);
    }
}

auto make_error(il::CompilerErrorType err) -> il::ErrorOr<il::ParseTree> {
    return std::unexpected<il::CompilerError>(il::CompilerError(err, "", 0));
}

struct ExpOut {
    static auto one() {
        using namespace il;
        ParseTree out;

        Expr expr;
        expr.push_back(LiteralExpr(1));
        out.exprs.push_back(expr);

        return out;
    }
    static auto minus_one() {
        using namespace il;
        ParseTree out;

        Expr expr;
        auto i0{expr.push_back(LiteralExpr(1))};
        expr.push_back(UnaryExpr(UnaryExpr::Op::minus, i0));
        out.exprs.push_back(expr);

        return out;
    }
    static auto plus_one() {
        using namespace il;
        ParseTree out;

        Expr expr;
        auto i0{expr.push_back(LiteralExpr(1))};
        expr.push_back(UnaryExpr(UnaryExpr::Op::plus, i0));
        out.exprs.push_back(expr);

        return out;
    }
    static auto group_one() {
        using namespace il;
        ParseTree out;

        Expr expr;
        auto i0{expr.push_back(LiteralExpr(1))};
        expr.push_back(GroupingExpr(i0));
        out.exprs.push_back(expr);

        return out;
    }
    static auto one_plus_one() {
        using namespace il;
        ParseTree out;

        Expr expr;
        auto i0{expr.push_back(LiteralExpr(1))};
        auto i1{expr.push_back(LiteralExpr(1))};
        auto i2{expr.push_back(BinaryExpr(i0, TokenType::plus, i1))};
        out.exprs.push_back(expr);

        return out;
    }
    static auto one_plus_two_times_three() {
        using namespace il;
        ParseTree out;

        Expr expr;
        auto i0{expr.push_back(LiteralExpr(1))};
        auto i1{expr.push_back(LiteralExpr(2))};
        auto i2{expr.push_back(LiteralExpr(3))};
        auto i4{expr.push_back(BinaryExpr(i1, TokenType::star, i2))};
        auto i3{expr.push_back(BinaryExpr(i0, TokenType::plus, i4))};
        out.exprs.push_back(expr);

        return out;
    }
};

static std::vector<ParserTestInput> parser_inputs{
    {"empty_file", "", {}},
    {"semicolon", ";", {}},
    {"one", "1;", ExpOut::one()},
    {"minus_one", "-1;", ExpOut::minus_one()},
    {"plus_one", "+1;", ExpOut::plus_one()},
    {"group_one", "(1);", ExpOut::group_one()},
    {"one_plus_one", "1 + 1;", ExpOut::one_plus_one()},
    {"one_plus_two_times_three", "1 + 2 * 3;", ExpOut::one_plus_two_times_three()},
    // Errors
    {"plus", "+", make_error(il::CompilerErrorType::unexpected_token)},
};
INSTANTIATE_TEST_SUITE_P(ParserTests,
                         ParserTest,
                         testing::ValuesIn(parser_inputs),
                         [](auto const& info) { return std::string(info.param.test_name); });
