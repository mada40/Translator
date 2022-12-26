#include "translator.h"
#include <gtest.h>
#include <iostream>
#include <cmath>

TEST(, can_solve_negative_number)
{
    const double res = -5.25 * -10.3;
    Translator tr(" -5.25 * -10.3 ");
    EXPECT_DOUBLE_EQ(tr.solve(), res);
}
TEST(, cant_solve_empty_expr)
{
    Translator tr(" ");
    ASSERT_ANY_THROW(tr.solve());
}

TEST(, cant_solve_invalid_expr1)
{
    Translator tr("d");
    ASSERT_ANY_THROW(tr.solve());
}
TEST(, cant_solve_invalid_expr2)
{
    Translator tr("*5");
    ASSERT_ANY_THROW(tr.solve());
}
TEST(, cant_solve_invalid_expr3)
{
    Translator tr("+5");
    ASSERT_ANY_THROW(tr.solve());
}

TEST(, Add)
{
    Translator tr("5.25 + 10.3");
    EXPECT_DOUBLE_EQ((5.25 + 10.3), tr.solve());
}
TEST(, Sub)
{
    Translator tr("5.25 - 10.3");
    EXPECT_DOUBLE_EQ((5.25 - 10.3), tr.solve());
}
TEST(, Mul)
{
    Translator tr("5.25 * 10.3");
    EXPECT_DOUBLE_EQ((5.25 * 10.3), tr.solve());
}
TEST(, Div)
{
    Translator tr("5.25 / 10.3");
    EXPECT_DOUBLE_EQ((5.25 / 10.3), tr.solve());
}
TEST(, can_solve_natural_number_mod1)
{
    Translator tr("18 % 3");
    EXPECT_DOUBLE_EQ((18 % 3), tr.solve());
}

TEST(, cant_solve_double_number_mod1)
{
    Translator tr(" 18 % 3.5 ");
    ASSERT_ANY_THROW(tr.solve());
}
TEST(, cant_solve_double_number_mod2)
{
    Translator tr(" 18.5 % 3 ");
    ASSERT_ANY_THROW(tr.solve());
}
TEST(, cant_div_zero)
{
    Translator tr("5.25 / ( 1 - 1 )");
    ASSERT_ANY_THROW(tr.solve());
}
TEST(, sum)
{
    Translator tr("1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10");
    EXPECT_EQ(55, tr.solve());
}

TEST(, cant_solve_expr_with_incorrect_opened_brackets)
{
    Translator tr("( 5.25 / 8.0 ");
    ASSERT_ANY_THROW(tr.solve());
}

TEST(, cant_solve_expr_with_incorrect_closed_brackets)
{
    Translator tr(" 5.25 / 8.0 )");
    ASSERT_ANY_THROW(tr.solve());
}

TEST(, cant_solve_expr_with_incorrect_brackets)
{
    Translator tr(" 5.25 / 8.0 ()");
    ASSERT_ANY_THROW(tr.solve());
}

TEST(, can_solve_hard_expr)
{
    const double res = ( 5.5 + 8.1 ) / 3 - 5.8 * ( 1.6 - 177.55 ) + 8 - 0.0008;
    Translator tr(" ( 5.5 + 8.1 ) / 3 - 5.8 * ( 1.6 - 177.55 ) + 8 - 0.0008");
    EXPECT_EQ(tr.solve(), res);
}


TEST(, cant_solve_incorrect_expr1)
{
    Translator tr(" 5.a5 / 8.0 ()");
    ASSERT_ANY_THROW(tr.solve());
}

TEST(, cant_solve_incorrect_expr2)
{
    Translator tr(" 5.5a / 8.0 ()");
    ASSERT_ANY_THROW(tr.solve());
}
TEST(, cant_solve_incorrect_expr3)
{
    Translator tr(" a / 8.0 ()");
    ASSERT_ANY_THROW(tr.solve());
}

TEST(, can_solve_expr_with_e1)
{
    const double res = (5.5 + E) / 3 - 5.8 * (1.6 - 177.55) + 8 - 0.0008;
    Translator tr(" ( 5.5 + e ) / 3 - 5.8 * ( 1.6 - 177.55 ) + 8 - 0.0008");
    EXPECT_EQ(tr.solve(), res);
}

TEST(, can_solve_expr_with_e2)
{
    const double res = (5.5 + E) / 3 - 5.8 * (1.6 - 177.55) + 8 - 0.0008;
    Translator tr(" ( 5.5 + E ) / 3 - 5.8 * ( 1.6 - 177.55 ) + 8 - 0.0008");
    EXPECT_EQ(tr.solve(), res);
}

TEST(, can_solve_expr_with_pi1)
{
    const double res = (5.5 + PI) / 3 - 5.8 * (1.6 - 177.55) + 8 - 0.0008;
    Translator tr(" ( 5.5 + Pi ) / 3 - 5.8 * ( 1.6 - 177.55 ) + 8 - 0.0008");
    EXPECT_EQ(tr.solve(), res);
}

TEST(, can_solve_expr_with_pi2)
{
    const double res = (5.5 + PI) / 3 - 5.8 * (1.6 - 177.55) + 8 - 0.0008;
    Translator tr(" ( 5.5 + pi ) / 3 - 5.8 * ( 1.6 - 177.55 ) + 8 - 0.0008");
    EXPECT_EQ(tr.solve(), res);
}


TEST(, can_solve_expr_with_var1)
{
    const double res = 5.5 + 25.0;
    Translator tr(" Abober + 5.5 ");

    tr.solve(std::map<std::string, double>{ { "Abober", 25.0 }});
    EXPECT_EQ(tr.solve(), res);
}

TEST(, can_solve_expr_with_var2)
{
    const double res = (10 + -5) * 5.5;
    Translator tr(" ( A + B ) * 5.5 ");

    auto res_tr = tr.solve(std::map<std::string, double>{ { "A", 10.0}, {"B", -5}});
    EXPECT_EQ(res_tr, res);
}

TEST(, can_solve_expr_with_var3)
{
    const double res = (10 + 10) * 5.5;
    Translator tr(" ( A + A ) * 5.5 ");

    auto res_tr = tr.solve(std::map<std::string, double>{ { "A", 10.0}});
    EXPECT_EQ(res_tr, res);
}


TEST(, can_solve_expr_with_sin_and_sin)
{
    const double res = 1.0;
    Translator tr(" cos ( PI ) * cos ( Pi ) + sin ( iP ) + sin ( iP )");

    auto res_tr = tr.solve();
    EXPECT_EQ(res_tr, res);
}
