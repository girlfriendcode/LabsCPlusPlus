
#include "gtest/gtest.h"
#include "../src/lab2.16.cpp"

TEST(ChainConstructor, DefaultConstructor)
{
    Prog2::ChainLine a;
    ASSERT_EQ(1, a.get_a());
}

TEST(ChainConstructor, TestException)
{
    ASSERT_ANY_THROW(Prog2::ChainLine(0));
}

// ňĺńňčđîâŕíčĺ äđóăčő ěĺňîäîâ
TEST(ChainMethods, Setters)
{
    Prog2::ChainLine r;
    r.set_a(1.5);
    ASSERT_EQ(1.5, r.get_a());
    r.set_a(-2.3);
    ASSERT_EQ(-2.3, r.get_a());
    ASSERT_ANY_THROW(r.set_a(0));
}

TEST(ChainMethods, Parameters)
{
    Prog2::ChainLine q;
    const double PI = 3.62686, err = 0.00001;
    ASSERT_NEAR(PI, q.getArea(0,2), err);
    ASSERT_NEAR(PI, q.getLength(0,2), err);
    ASSERT_NEAR(sinh(2) - sinh(0), q.getArea(0, 2), err);
    ASSERT_NEAR(sinh(2) - sinh(0), q.getLength(0, 2), err);
    ASSERT_NEAR(0, q.getArea(3, 3), err);
    ASSERT_NEAR(0, q.getLength(3, 3), err);
    ASSERT_EQ(1, q.getRadius(0));
    ASSERT_EQ(0, q.getCenter(0).x);
    ASSERT_EQ(2, q.getCenter(0).y);
    ASSERT_EQ(1, q.get_Y(0));

    Prog2::ChainLine p(3);
    ASSERT_NEAR(6.45443, p.getArea(0, 2), err);
    ASSERT_NEAR(2.15148, p.getLength(0, 2), err);
    double a = 22.55047, b = -15.997, c = 16.4501;
    ASSERT_NEAR(a, p.getRadius(5), 0.0001);
    ASSERT_NEAR(b, p.getCenter(5).x, 0.0001);
    ASSERT_NEAR(c, p.getCenter(5).y, 0.0001);
    ASSERT_EQ(3, p .get_Y(0));

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

