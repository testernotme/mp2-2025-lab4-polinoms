
#include "Polinome.h"
#include <gtest.h>
TEST(Polinome, can_create_pol)
{
	ASSERT_NO_THROW(Polinome a);
}
TEST(Polinome, can_create_not_in_order_pol)
{
	ASSERT_NO_THROW(Polinome a("12y2z5x1"));
}
TEST(Polinome, can_double_const_pol)
{
	Polinome a("-12.31x1y4z3");
	EXPECT_EQ(a.print(), "-12.31x1y4z3");
}
TEST(Polinome, can_add_elements_to_polinome)
{
	Polinome a("3123x1y4z3");
	a.add("12x1y2z3");
	a.add("12x2y2z3");
	EXPECT_EQ(a.print(), "12x1y2z3 + 3123x1y4z3 + 12x2y2z3");
}
TEST(Polinome, can_add_float_elements_to_polinome)
{
	Polinome a("3123x1y4z3");
	a.add("-1.2x1y2z3");
	EXPECT_EQ(a.print(), "-1.2x1y2z3 + 3123x1y4z3");
}
TEST(Polinome, can_return_size)
{
	Polinome a("3123x1y4z3");
	EXPECT_EQ(a.size(), 1);
	a.add("12x1y2z3");
	EXPECT_EQ(a.size(), 2);
}
TEST(Polinome, can_sum_polinome)
{
	Polinome a("3123x1y4z3");
	Polinome b("12x1y2z3");
	Polinome c(a+b);
	EXPECT_EQ(c.print(), "12x1y2z3 + 3123x1y4z3");
}
TEST(Polinome, can_sum_polinome_const)
{
	Polinome a("3123x1y4z3");
	Polinome b("12x1y4z3");
	Polinome c(a + b);
	EXPECT_EQ(c.print(), "3135x1y4z3");
}
TEST(Polinome, can_be_polinome_zero_const)
{
	Polinome a("-12x1y4z3");
	Polinome b("12x1y4z3");
	Polinome c(a + b);
	EXPECT_EQ(c.print(), "");
}
TEST(Polinome, can_mult_polinome)
{
	Polinome a("1x1y4z3+3x1y1z1");
	Polinome b("12x1y4z3");
	Polinome c(a * b);
	EXPECT_EQ(c.print(), "36x2y5z4 + 12x2y8z6");
}
TEST(Polinome, can_mult_be_zero_polinome)
{
	Polinome a("1x1y1z1+1x2y2z2");
	Polinome b("1x1y1z1-1x2y2z2");
	Polinome c(a * b);
	EXPECT_EQ(c.print(), "1x2y2z2 + -1x4y4z4");
}