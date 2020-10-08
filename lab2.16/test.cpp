#include "pch.h"
#include <iostream>
#include <tuple>
#include "gtest/gtest.h"
#include "../Lab2_lib/ChainLine.cpp"
TEST(ChainLineConstructor, defaultConstructor) {
	Prog2::ChainLine a1;
	ASSERT_EQ(1, a1.get_a());
	ASSERT_EQ(-1, a1.get_x1());
	ASSERT_EQ(1, a1.get_x2());
}

TEST(ChainLineConstructor, InitConstructors) {
	Prog2::ChainLine a2(3);
	ASSERT_EQ(3, a2.get_a());
	ASSERT_EQ(-1, a2.get_x1());
	ASSERT_EQ(1, a2.get_x2());

	Prog2::ChainLine a3(4, 5);
	ASSERT_EQ(4, a3.get_a());
	ASSERT_EQ(5, a3.get_x1());
	ASSERT_EQ(1, a3.get_x2());

	Prog2::ChainLine a4(3, 2, 6);
	ASSERT_EQ(3, a4.get_a());
	ASSERT_EQ(2, a4.get_x1());
	ASSERT_EQ(6, a4.get_x2());
}

TEST(ChainLineConstructor, TestException) {
	ASSERT_ANY_THROW(Prog2::ChainLine(0));
	ASSERT_ANY_THROW(Prog2::ChainLine(0, 2));
	ASSERT_ANY_THROW(Prog2::ChainLine(0, 2, 5));
}
TEST(ChainLineMethods, Setters) {
	Prog2::ChainLine ch;
	ch.set_x1(5);
	ch.set_x2(4);
	ASSERT_EQ(5, ch.get_x1());
	ASSERT_EQ(4, ch.get_x2());
	ch.set_x1(-5);
	ch.set_x2(-4);
	ASSERT_EQ(-5, ch.get_x1());
	ASSERT_EQ(-4, ch.get_x2());
	ch.set_a(2);
	ASSERT_EQ(2, ch.get_a());
	ASSERT_ANY_THROW(ch.set_a(0));
}

TEST(ChainLineMethods, Parameters)
{
	Prog2::ChainLine a5;
	const double err = 0.00001;
	ASSERT_NEAR(2.35040, a5.getLength(-1, 1), err);
	ASSERT_NEAR(2.35040, a5.getArea(-1, 1), err);
	ASSERT_NEAR(27.30823, a5.f(4), err);
	ASSERT_EQ(1, a5.getRadius(0));
	ASSERT_EQ(1, a5.f(0));
	double a = std::get<0>(a5.getCenter(4));
	double b = std::get<1>(a5.getCenter(4));
	ASSERT_NEAR(-741.23941, a, err);
	ASSERT_NEAR(54.61647, b, err);

	Prog2::ChainLine line(3, 1, 4);
	ASSERT_NEAR(5.50694, line.getLength(2, 5), err);
	ASSERT_NEAR(16.52083, line.getArea(2, 5), err);
	ASSERT_NEAR(8.22504, line.f(5), err);
	ASSERT_EQ(3, line.getRadius(0));
	ASSERT_NEAR(3.34586, line.getRadius(1), err);
	a = std::get<0>(line.getCenter(2));
	b = std::get<1>(line.getCenter(2));
	ASSERT_NEAR(-0.64755, a, err);
	ASSERT_NEAR(7.38345, b, err);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
