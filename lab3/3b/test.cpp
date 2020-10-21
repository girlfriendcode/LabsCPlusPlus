#include "pch.h"
#include "gtest/gtest.h"
#include "../Lab3_2_lib/HexNumber.h"
#include "../Lab3_2_lib/HexNumber.cpp"

TEST(HexConstructor, Constructors) {
    Prog3::HexNumber2 a;
    char aa[8] = { 'a', 'a', 'a', '.', 'a', 'a', 'a', 'a' }, bb[40] = { '-', 'a', 'a', 'e', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', '5', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', 'b', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', 'c', 'a', 'a', 'a', 'a' ,'a', 'a', 'a', 'd', 'a', 'a', 'a', 'a' };
    ASSERT_EQ('0', a.getSign());
    Prog3::HexNumber2 c(bb);
    ASSERT_EQ('F', c.getSign());
    Prog3::HexNumber2 d(-0x846fed);
    ASSERT_EQ('F', d.getSign());
}
TEST(HexConstructor, TestException) {
    ASSERT_ANY_THROW(Prog3::HexNumber2("fgfgsgsgegb"));
    ASSERT_ANY_THROW(Prog3::HexNumber2("abcdef=d=+D"));
}
TEST(HexMethods, ParityCheck) {
    Prog3::HexNumber2 a(0x5624fe), b(-0xdfabef), c;
    ASSERT_EQ(0, a.Parity());
    ASSERT_EQ(1, b.Parity());
    ASSERT_EQ(0, c.Parity());
}
TEST(HexMethods, Compare) {
    char n1[4] = { '0','5','f','\0' }, n2[3] = { '5','F', '\0' };
    Prog3::HexNumber2 a(0x5624f), b(-0xdfabe), c(n1), d(n2);
    ASSERT_EQ('>', a.Compare(b));
    ASSERT_EQ('>', a.Compare(c));
    ASSERT_EQ('<', b.Compare(c));
    ASSERT_EQ('>', c.Compare(d));
}
TEST(HexMethods, Convert) {
    Prog3::HexNumber2 d(-0x846fed);
    Prog3::HexNumber2 c = d.Convert().Convert();
    ASSERT_EQ('=', c.Compare(d));
}
TEST(HexMethods, Add) {
    Prog3::HexNumber2 a(0x5624f), b(-0xdfabe), c, d(-0x8986F);
    c = a + b;
    ASSERT_EQ('<', c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f' , '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    Prog3::HexNumber2 e(bb), f(-1), t(0xfedabc), g(bc);
    ASSERT_EQ('=', g.Compare(e+t));
}
TEST(HexMethods, Subtract) {
    Prog3::HexNumber2 a(0x5624f), b(-0xdfabe), c, d(-0x8986F);
    c = a-b;
    ASSERT_EQ('>', c.Compare(d));
    char bb[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f','f','f','f' , '\0' };
    char bc[33] = { '-', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '0', '1', '2','5','4','3' , '\0' };
    Prog3::HexNumber2 e(bb), f(2), t(-0xfedabc), g(bc);
    ASSERT_EQ('=', g.Compare(e-t));
}
TEST(HexMethods, Move) {
    Prog3::HexNumber2 a(0x5624f), b(0x56), c, d(0x5600000);
    a>>=3;
    ASSERT_EQ('=', a.Compare(b));
    a<<=5;
    ASSERT_EQ('=', a.Compare(d));
    a>>=20;
    ASSERT_EQ('=', a.Compare(c));
    b<<=35;
    ASSERT_EQ('=', b.Compare(c));
}
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
