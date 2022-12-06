#include "translator.h"
#include <gtest.h>
#include <iostream>
TEST(, cant_solve_empty_expr)
{
    ASSERT_ANY_THROW(solve(" "));
}
TEST(, cant_solve_invalid_expr1)
{
    ASSERT_ANY_THROW(solve("d"));
}
TEST(, cant_solve_invalid_expr2)
{
    ASSERT_ANY_THROW(solve("*5"));
}
TEST(, cant_solve_invalid_expr3)
{
    ASSERT_ANY_THROW(solve("+5"));
}
TEST(, can_solve_ones_number)
{
    EXPECT_DOUBLE_EQ(5.28, solve("5.28"));
}
TEST(, Add)
{
    EXPECT_DOUBLE_EQ((5.25 + 10.3), solve(" 5.25 + 10.3 "));
}
TEST(, Sub)
{
    EXPECT_DOUBLE_EQ((5.25 - 10.3), solve(" 5.25 - 10.3 "));
}
TEST(, Mul)
{
    EXPECT_DOUBLE_EQ((5.25 * 10.3), solve(" 5.25 * 10.3 "));
}
TEST(, Div)
{
    EXPECT_DOUBLE_EQ((5.25 / 10.3), solve(" 5.25 / 10.3 "));
}
TEST(, can_solve_natural_number_mod1)
{
    EXPECT_DOUBLE_EQ((18 % 3), solve(" 18 % 3 "));
}
TEST(, can_solve_natural_number_mod2)
{
    EXPECT_DOUBLE_EQ((18 % 3), solve(" 18.0 % 3.0 "));
}
TEST(, cant_solve_double_number_mod1)
{
    ASSERT_ANY_THROW(solve(" 18 % 3.5 "));
}
TEST(, cant_solve_double_number_mod2)
{
    ASSERT_ANY_THROW(solve(" 18.5 % 3 "));
}
TEST(, cant_div_zero)
{
    ASSERT_ANY_THROW(solve("5.25 / ( 1 - 1 )"));
}
TEST(, sum)
{
    EXPECT_EQ(55, solve("1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10"));
}

TEST(, cant_solve_expr_with_incorrect_opened_brackets)
{
    ASSERT_ANY_THROW(solve("( 5.25 / 8.0 "));
}

TEST(, cant_solve_expr_with_incorrect_closed_brackets)
{
    ASSERT_ANY_THROW(solve(" 5.25 / 8.0 )"));
}

TEST(, cant_solve_expr_with_incorrect_brackets)
{
    ASSERT_ANY_THROW(solve(" 5.25 / 8.0 ()"));
}

TEST(, can_solve_hard_expr)
{
    const double res = ( 5.5 + 8.1 ) / 3 - 5.8 * ( 1.6 - 177.55 ) + 8 - 0.0008;
    EXPECT_EQ(solve(" ( 5.5 + 8.1 ) / 3 - 5.8 * ( 1.6 - 177.55 ) + 8 - 0.0008"), res);
}


TEST(, cant_solve_incorrect_expr1)
{
    ASSERT_ANY_THROW(solve(" 5.a5 / 8.0 ()"));
}

TEST(, cant_solve_incorrect_expr2)
{
    ASSERT_ANY_THROW(solve(" 5.5a / 8.0 ()"));
}
TEST(, cant_solve_incorrect_expr3)
{
    ASSERT_ANY_THROW(solve(" a / 8.0 ()"));
}
