#pragma once
#include <iostream>
namespace Prog3 {
	class HexNumber
	{
	private:
		static const int maxLen = 32;
		char hex[maxLen];
		int length;//длина введённого пользователем символьного массива
	public:
		HexNumber();
		HexNumber(char* str);
		HexNumber(const long int a);
		HexNumber(const HexNumber& number);
    
		char getSign()const;
		char getElement(int i)const;
    
		std::ostream& output(std::ostream& o);
		std::istream& input(std::istream& i);
    
		HexNumber& setN(char* str);
    HexNumber& Convert();
		const HexNumber Add(const HexNumber& num);
		const HexNumber Sub(const HexNumber& num);
    
		HexNumber& moveRight(int a);
		HexNumber& moveLeft(int a);
		
		char Compare(const HexNumber& num);//сравнение
		int Parity();//чётность
	};
	void out(HexNumber&, HexNumber&, HexNumber&, const char*);
  void dialog(HexNumber&, HexNumber&);
  
	char upper(char num);
  
	int CharToHex(char num);
	char HexToChar(int num);
	
}


