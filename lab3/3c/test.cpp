#include "pch.h"
#include "gtest/gtest.h"
#include "../lab3final/HexNumber.h"
#include "../lab3final/HexNumber.cpp"
TEST(HexConstructor, Constructors) {
    Prog3::HexNumber a;
    char aa[8] = { 'a', 'a', 'w', '.', 'a', 'a', 'a', '\0' };
    char bb[36] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a','a','a', 'a', 'a', 'a', 'a', 'a', 'a','a', 'a', 'a', 'a', 'a', 'a', 'a', 'a','a', 'a', 'a', 'a', 'a', 'a', 'a', 'a','a','a', 'a', 'a','\0', };
    ASSERT_EQ('0', a.getSign());
    Prog3::HexNumber c(bb);//с помощью строки
    ASSERT_EQ('0', c.getSign());
    Prog3::HexNumber d(0x846fed), m(d); //с помощью константы
    ASSERT_EQ('=', m.Compare(d));
    ASSERT_EQ('0', d.getSign());
}
TEST(HexConstructor, TestException) {
    ASSERT_ANY_THROW(Prog3::HexNumber("fgfgsgsgegb"));
    ASSERT_ANY_THROW(Prog3::HexNumber("abcdef=d=+D"));
}
TEST(HexMethods, ParityCheck) { //проверка четности
    Prog3::HexNumber a(0x5624fe), b(-0xdfabef), c;
    ASSERT_EQ(0, a.Parity());
    ASSERT_EQ(1, b.Parity());
    ASSERT_EQ(0, c.Parity());
}
TEST(HexMethods, Compare) { //сравнение
    char n1[4] = { '0','5','f','\0' }, n2[3] = { '5','F', '\0' };
    Prog3::HexNumber a(0x5624f), b(-0xdfabe), c(n1), d(n2);
    ASSERT_EQ('>', a.Compare(b));//>
    ASSERT_EQ('<', a.Compare(c));
    ASSERT_EQ('<', b.Compare(c));
    ASSERT_EQ('=', c.Compare(d));
    Prog3::HexNumber m(b);
    ASSERT_EQ('=', m.Compare(b));
}
TEST(HexMethods, Convert) { //перевод в доп. код
    Prog3::HexNumber d(-0x846fed);
    Prog3::HexNumber c = d.Convert().Convert();
    ASSERT_EQ('=', c.Compare(d));//=
}
TEST(HexMethods, Move) { //сдвиги
    Prog3::HexNumber a(0x5624f), b(0x56), c, d(0x5600000), k(500);
    ASSERT_ANY_THROW(k >>= -1);
    ASSERT_ANY_THROW(k <<= -1);
    a >>= 3;
    ASSERT_EQ('=', a.Compare(b));
    a <<= 5;
    ASSERT_EQ('=', a.Compare(d));
    a >>= 20;
    ASSERT_EQ('=', a.Compare(c));
    b <<= 35;
    ASSERT_EQ('>', b.Compare(c));
}
TEST(HexMethods, Plus) {
    Prog3::HexNumber a(123), b(4), d(127);
    Prog3::HexNumber c(a + b);
    ASSERT_EQ('=', c.Compare(d));//
}
TEST(HexMethods, Minus) {
    Prog3::HexNumber a(0x5624f), b(0xdfabe),c, d(-0x8986F);
    
    ASSERT_EQ('>', c.Compare(d));
    Prog3::HexNumber e(b), f(2), t(0xabcdef), g(-0x9dd331);
    ASSERT_EQ('=', g.Compare(e - t));
}

int _tmain(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
