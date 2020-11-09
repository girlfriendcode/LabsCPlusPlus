#include "pch.h"
#include "HexNumber.h"
#include <iostream>
#include <string.h>
#include <cctype>
#include <stdexcept> 
#include <algorithm>
#include <iterator>
#include <stdio.h>

namespace Prog3 {
	HexNumber::HexNumber() {
		length = 1;
		hex = new char[2];
		hex[0] = '0';
		hex[1] = '0';
	}
	HexNumber::HexNumber(const char* str):HexNumber() {
		try {
			setN(str);
		}
		catch (std::exception&) {
			throw std::invalid_argument("Wrong data");

		}
	}
	HexNumber::HexNumber(const int A) {
		int a = A, b = A, size = 0;
		char sign = '0';
		if (a < 0) {
			sign = 'F';
			a = -a;
			b = a;
		}
		for (; b; size++)
			b >>= 4;
		hex = new char[size + 1];
		int i = size;
		hex[0] = sign;
		for (; a; i--) {
			hex[i] = HexToChar(a % 0x10);
			a >>= 4;
		}
		length = size;
		if (!length) {
			char* a = hex;
			length = 1;
			hex = new char[2];
			hex[0] = '0';
			hex[1] = '0';
			delete a;
		}
	}

	HexNumber::HexNumber(const HexNumber& other)
	{
		try {
			length = other.length;
			hex = new char[length + 1];
			for (int i = 0; i < length + 1; i++)
				hex[i] = other.hex[i];
		}
		catch (...) {
			std::cout <<std::endl<< "Empty initialization"<<std::endl;
			length = 1;
			hex = new char[2];
			hex[0] = hex[1] = '0';
		}
	}
	HexNumber::HexNumber(HexNumber&& A) :length(A.length), hex(A.hex) {
		
		A.hex = nullptr;
	}


	HexNumber& HexNumber::setN( const char* str)
	{ 
		int leng = strlen(str);
		int i = 0;
		char sign = '0';
		switch (str[0]) {
		case '+':
			i++;
			break;
		case '-':
			sign = 'F';
			i++;
			break;
		default:
			sign = '0';
		}
		if (str[i] == '0' && str[i + 1] == 'x')
			i += 2;
		while (str[i] == '0')
			i++;
		int size = leng - i;//длина цифровой части
		if (size > 32)
			size = 32;
		try {
			hex = new char[size + 1];
		}
		catch (std::exception& a) {
			throw std::exception("Memory allocation error");
		}
		hex[0] = sign;
		int ll = 1;
		length = size;
		for (; ll <size+1; i++, ll++) {
			if (!isxdigit(str[i]))//проверка попадания символа в диапазон шестнадцатиричных цифр
				throw std::exception("Invalid symbol");
			hex[ll] = toupper(str[i]);
		}
		if ((hex[0] == 'F' && length == 1 && hex[1] == '0') || !length) {//если число -ноль
			HexNumber c;
			*this = c;
		}
		return *this;

	}
	
	void HexNumber::Format(int k)
	{
		int new_size = length + k + 1;
		char* a = hex;
		hex = new char[new_size];
		hex[0] = a[0];
		for (int i = k + 1; i < new_size; i++)
			hex[i] = a[i - k];
		for (int i = 1; i <= k; i++)
			hex[i] = '0';
		length += k;
		delete[] a;
	}

	HexNumber& HexNumber::Convert() {
		for (int i = 1; i <= length; i++) { //инверитруем все разряды кроме знакового
			int n = 0xF - CharToHex(hex[i]);
			hex[i] = HexToChar(n);
		}
		int l = length;
		while (l > 0 && hex[l] == 'F') // поиск места для добавления единицы
			l--;
		if (l == 0) // если места нет произошло переполнение
			throw std::exception("Incorrect operand");
		int k = CharToHex(hex[l]) + 1;
		hex[l] = HexToChar(k); //добавляем единицу в найденное место
		for (int i = l + 1; i <= length; i++)
			hex[i] = '0';
		return *this;
	}
	int HexNumber::Parity() const {
		if (hex[length] >= '0' && hex[length] <= '9') {
			return ((int)hex[length] - 48) % 2;
		}
		switch (hex[length]) {
		case 'B':
		case 'D':
		case 'F':
			return 1;
		case 'A':
		case 'C':
		case 'E':
			return 0;
		}
		return -1;
	}
	
	bool HexNumber::operator>(const HexNumber& other) const
	{
		if (hex[0] == other.hex[0]) {
			int l = length;
			if (other.length > length)
				l = other.length;
			char sgn = getSign();

			for (int i = 1; i < length + 1; i++) {
				if (hex[i] > other.hex[i])
					return sgn == '0';
				else
					return sgn == 'F';
			}
		}
		else return hex[0] == '0';
	}
	bool HexNumber::operator==(const HexNumber& other) const
	{
  
		HexNumber first = *this, second = other;
		if (first.getSign() != second.getSign()) return false;
		else {
			int l = first.length;
			if (second.length > first.length) {
				l = second.length;
				first.Format(l - length);
			}
			else
				second.Format(length - second.length);
			for (int i = 1; i < length + 1; i++)
				if (hex[i] != other.hex[i]) return false;
		}
		return true;
	}
	char HexNumber::Compare(const HexNumber& other) const
	{
		if (*this == other)
			return '=';
		else if (*this > other)
			return '>';
		else
			return '<';
	}
	std::istream& operator>>(std::istream& istr, HexNumber& num)
	{  
		std::string str;
		istr >> str;

		num.setN(str.c_str());

		return istr;
		
	}
	std::ostream& operator<<(std::ostream& ostr, const HexNumber& num)
	{
		if (num.hex[0] == 'F')
			ostr << "-";
		for (int j = 1; j <= num.length; j++)
			ostr << num.hex[j];
		return ostr;
	}
	HexNumber& HexNumber::operator=(HexNumber& other) {
		length = other.length;
		hex = new char[length + 1];
		for (int i = 0; i < length + 1; i++)
			hex[i] = other.hex[i];
		return *this;

	}
	HexNumber& HexNumber::operator =(HexNumber&& A) {
		length = A.length;
		hex = A.hex;
		A.hex = nullptr;
		return *this;
	}

	HexNumber& HexNumber::operator>>=(const int a)//сдвиг влево
	{
		if (a < 0)
			throw std::exception("Invalid input");
		if (a == 0)
			return *this;
		if (a >= length) {//выходим за пределы 32 знаков слева
			HexNumber object;//пустой конструктор on
			*this = object;
			return *this;
		}
		length -= a;
		char* buf = hex;
		try {
			hex = new char[length + 1];
		}
		catch (std::exception& a) {
			throw std::exception("Memory allocation error");
		}
		std::copy(buf, buf + length + 1, hex);
		delete[] buf;
		return *this;
	}

	HexNumber& HexNumber::operator<<=(const int a)//сдвиг влево
	{
		if (a < 0)
			throw std::exception("Invalid input");
		if (a == 0)
			return *this;
		if (hex[0] == '0' && hex[1] == '0' && length == 1) {//ноль никак не расширим
			HexNumber object(0);//пустой конструктор on
			*this = object;
			return *this;
		}
		int l = length;
		length += a;
		char* buf = hex;
		try {
			hex = new char[length + 1];
		}
		catch (std::exception& a) {
			throw std::exception("Memory allocation error");
		}
		int i = 0;
		for (; i <= l; i++)
			hex[i] = buf[i];//cдвигаем влево
		for (; i <= length; i++)
			hex[i] = '0';//заполняем освободившиеся клетки нулями
		delete[] buf;
		return *this;

	}
	HexNumber& HexNumber::operator+() const
	{
		HexNumber result(*this);
		result.hex[0] = '0';
		return result;
	}
	HexNumber& HexNumber::operator+ (const HexNumber& other)
	{
  
		HexNumber F(*this), Second(other);
		if (Second.length == 1 && Second.hex[1] == '0')//если второй операнд 0 возвращаем первый операнд
			return F;
		int l = length + 1, flag = 0;
		if (Second.length > length) {
			l = Second.length + 1;
		}
		F.Format(l - F.length);
		Second.Format(l - Second.length);//дополняем нулями
		HexNumber res(F);
		if (F.hex[0] == 'F') //перевод чисел в дополнительный код при надобности
			F.Convert();
		if (Second.hex[0] == 'F')
			Second.Convert();
		int transfer = 0;// transfer - перенос из младшего разряда
		res.hex = new char[l + 1];
    
		for (int i = F.length; i > -1; i--) { //сложение чисел
			int sum = CharToHex(F.hex[i]) + CharToHex(Second.hex[i]) + transfer;
			res.hex[i] = HexToChar((sum) % 0x10);
			transfer = 0;
			if (sum >>= 4)
				transfer = 1;
		}
    
		if (res.hex[0] == 'F')
			res.Convert();
		int k = 1;
		while (res.hex[k] == '0') //вычисление длины результата
			k++;
		char* buf = res.hex;
		res.length = l + 1 - k;
		int len = res.length + 1;
		res.hex = new char[len];
		if (k != 1) {
			res.hex[0] = buf[0];
			for (int i = 1; i <res.length+1; i++)
				res.hex[i] = buf[k + i - 1];
		}
		delete[] buf;
    
		if (!res.length) {
			delete[] res.hex;
			HexNumber a(0);
			res = a;
			delete[] a.hex;
		}
    
		*this = res;
		return *this;
	}

	HexNumber& HexNumber::operator-(const HexNumber& other)
	{
		HexNumber second = other, res;
		if (second.hex[0] == '0') //домножаем второй операнд на -1
			second.hex[0] = 'F';
		else
			second.hex[0] = '0';
		res = *this + second;
		return res;
	}


	int CharToHex(char num) {
		switch (num) {
		case '0': return 0x0;
		case '1': return 0x1;
		case '2': return 0x2;
		case '3': return 0x3;
		case '4': return 0x4;
		case '5': return 0x5;
		case '6': return 0x6;
		case '7': return 0x7;
		case '8': return 0x8;
		case '9': return 0x9;
		case 'A': return 0xa;
		case 'B': return 0xb;
		case 'C': return 0xc;
		case 'D': return 0xd;
		case 'E': return 0xe;
		case 'F': return 0xf;
		}
		return -1;
	}

	char HexToChar(int num) {
		switch (num) {
		case 0x0: return '0';
		case 0x1: return '1';
		case 0x2: return '2';
		case 0x3: return '3';
		case 0x4: return '4';
		case 0x5: return '5';
		case 0x6: return '6';
		case 0x7: return '7';
		case 0x8: return '8';
		case 0x9: return '9';
		case 0xA: return 'A';
		case 0xB: return 'B';
		case 0xC: return 'C';
		case 0xD: return 'D';
		case 0xE: return 'E';
		case 0xF: return 'F';
		}
		return '/';
	}
}
