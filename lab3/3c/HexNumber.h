#include <iosfwd>
#ifndef __HEX_NUMBER_H__
#define __HEX_NUMBER_H__
namespace Prog3 {
	class HexNumber
	{
	private:
		char* hex;
		int length;
		
	public:
		
		HexNumber();
		HexNumber(const char* str);
		HexNumber(const int A);
		HexNumber(const HexNumber& other);
		~HexNumber() {delete[] hex;};
		HexNumber(HexNumber&& A);
		
		
		char getSign()const { return hex[0]; };
		HexNumber& Convert();
		HexNumber& setN(const char* str);
		int Parity() const;//чётность
		void Format(int k);//для увеличения сетки при +/-

		friend std::ostream& operator<< (std::ostream& ostr, const HexNumber&);
		friend std::istream& operator>> (std::istream& istr, HexNumber&);

		HexNumber& operator>>= (const int ); //cдвиг вправо 
		HexNumber& operator<<= (const int );//свдиг влево
		HexNumber& operator+() const; //унарный плюс
		HexNumber& operator+ (const HexNumber&);
		HexNumber& operator+= (const HexNumber& other) { return *this = *this + other; };
		HexNumber& operator- (const HexNumber& other);
		HexNumber& operator-= (const HexNumber& other) { return *this = *this - other; };
		HexNumber& operator= (const HexNumber& other);//копирующий оператор присваивания
		HexNumber& operator= (HexNumber&& other);
		HexNumber& operator= ( HexNumber& other);

		bool operator> (const HexNumber& other)const;
		bool operator< (const HexNumber& other)const { return !((*this > other) || (*this == other)); };
		bool operator== (const HexNumber& other)const;
		char Compare(const HexNumber& other)const;
		
	};
	void dialog(HexNumber& a, HexNumber& b);
	int CharToHex(char num);
	char HexToChar(int num);
}//namespace Prog3
#endif /*!__HEX_NUMBER_H */
