#include <iosfwd>
#ifndef __HEX_NUMBER_H__
#define __HEX_NUMBER_H__
namespace Prog3 {
	class HexNumber2
	{
	private:
		static const int MAX_LEN = 32;
		char hex[MAX_LEN];
		int length;//длина введённого пользователем символьного массива
	public:
		HexNumber2();
		HexNumber2(const char* str);
		HexNumber2(const long  a);
		HexNumber2(const HexNumber2& number);

		char getSign()const { return hex[0]; };

		HexNumber2& setN(const char* str);
		HexNumber2& Convert();

		int Parity() const;//чётность

		friend std::ostream& operator<< (std::ostream& ostr, const HexNumber2&);
		friend std::istream& operator>> (std::istream& istr, HexNumber2&);

		HexNumber2& operator>>= (const int a); //cдвиг вправо 
		HexNumber2& operator<<= (const int a);//свдиг влево

		HexNumber2& operator+() const; //унарный плюс
		HexNumber2& operator+ (const HexNumber2&);
		HexNumber2& operator+= (const HexNumber2& other) { return *this = *this + other; };
		HexNumber2& operator-() const;
		HexNumber2& operator- (const HexNumber2& other) { return *this + (-other); };
		HexNumber2& operator-= (const HexNumber2& other) { return *this = *this - other; };
		HexNumber2& operator= (const HexNumber2& other);

		bool operator> (const HexNumber2& other)const;
		bool operator< (const HexNumber2& other)const { return !((*this > other)||(*this == other)); };
		bool operator== (const HexNumber2& other)const;
		char Compare(const HexNumber2& other)const;
	};
	void dialog(HexNumber2& a, HexNumber2& b);
	int CharToHex(char num);
	char HexToChar(int num);
}
#endif /*!__HEX_NUMBER_H */
