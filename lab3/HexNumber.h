#include <iosfwd>
#ifndef __HEX_NUMBER_H__
#define __HEX_NUMBER_H__
#include <iostream>
namespace Prog3 {
	class HexNumber
	{
	private:
		static const int MAX_LEN = 32;
		char hex[MAX_LEN];
		int length;//длина введённого пользователем символьного массива
	public:
		HexNumber();
		HexNumber(char* str);
		HexNumber(const long  a);
		HexNumber(const HexNumber& number);
		
		HexNumber& operator= (const HexNumber& num);
		
		char getSign()const { return hex[0] ;};
		char getElement(int i)const { return hex[i] ;};
    
		std::ostream& output(std::ostream& o) const;
		std::istream& input(std::istream& i);
    
		HexNumber& setN(char* str);
                HexNumber& Convert();
	        HexNumber& Add(const HexNumber& num);
		HexNumber& Sub(const HexNumber& num);
    
		HexNumber& moveRight(int a);
		HexNumber& moveLeft(int a);
		
		char Compare(const HexNumber& num);//сравнение
		int Parity();//чётность
	};
	void out(HexNumber& op1, HexNumber& op2, HexNumber& res, const char*);
  
	int CharToHex(char num);
	char HexToChar(int num);
	
}
#endif /*!__HEX_NUMBER_H */

