#include "pch.h"
#include "HexNumber.h"
#include <iostream>
#include <string.h>
#include <cctype>
#include <stdexcept> 
#include <algorithm>
#include <iterator>
namespace Prog3 {
	HexNumber2::HexNumber2() : hex{},
		length(1)//пустой конструктор
	{
		std::fill(hex, hex + HexNumber2::MAX_LEN, '0');
	}
	HexNumber2::HexNumber2(const char* str)//инициализирующий строкой конструктор
	{
		try {
			setN(str);
		}
		catch (std::exception&) {
			throw std::invalid_argument("Wrong data");
		}
	}

	HexNumber2::HexNumber2(const long a)
	{
		int a2 = a;
		if (a < 0) {
			hex[0] = 'F';
			a2 = -a;
		}
		else
			hex[0] = '0';
		int i = HexNumber2::MAX_LEN - 1;
		for (; a2; i--) {
			hex[i] = HexToChar(a2 & 0xf);
			a2 >>= 4;
		}
		for (int j = 1; j <= i; j++)
			hex[j] = '0';
		length = HexNumber2::MAX_LEN - i - 1;
		if (!length)
			length = 1;
	}

	HexNumber2::HexNumber2(const HexNumber2& number) :hex{}, length(number.length)
	{
		std::copy(number.hex, number.hex + HexNumber2::MAX_LEN, hex);
	}

	HexNumber2& HexNumber2::setN(const char* str) {
		int leng = strlen(str), i = 0;
		if (!leng)
			throw std::exception("Wrong data");
		switch (str[0]) {//Проверка знака
		case '+':
			i++;
			break;
		case '-':
			hex[0] = 'F';
			i++;
			break;
		default:
			hex[0] = '0';
		}
		if (str[i] == '0' && str[i + 1] == 'x')//проверка ввода числа, начинающегося с 0x
			i += 2;
		while (str[i] == '0')//проверка ввода числа, начинающегося с 0
			i += 1;
		int ll = HexNumber2::MAX_LEN - leng + i;//место, с которого начинаем вводить число в массив
		if (ll < 1)
			ll = 1;
		for (int j = 1; j < ll; j++)// заполняем массив нулями до значащих цифр
			hex[j] = '0';
		length = ((leng - i) > 31) ? 31 : leng - i;
		for (int j = i; j < leng && ll < HexNumber2::MAX_LEN; j++, ll++) {
			if (!isxdigit((int)(str[j])))//проверка попадания символа в диапазон шестнадцатиричных цифр
				throw std::exception("Invalid symbol");
			hex[ll] = toupper(str[j]);
		}
		if (leng - i > 31)
			std::cout << "Only first 31 digits will be read" << std::endl;
		if ((hex[0] == 'F' && length == 1 && hex[HexNumber2::MAX_LEN - 1] == '0') || !length) {//если число -ноль
			HexNumber2 c;
			*this = c;
		}
		return *this;
	}

	HexNumber2& HexNumber2::Convert()//перевод в допкод с добавлением единицы для отрицательных чисел
	{
		for (int i = 1; i < HexNumber2::MAX_LEN; i++) {
			int n = 0xF - CharToHex(hex[i]);
			hex[i] = HexToChar(n);
		}
		int l = HexNumber2::MAX_LEN - 1;
		while (l > 0 && hex[l] == 'F')//поиск места для добавления единицы
			l--;
		if (l == 0)
			throw std::exception("Overflow");
		int k = CharToHex(hex[l] + 1);
		hex[l] = HexToChar(k);
		for (int i = l + 1; i < HexNumber2::MAX_LEN; i++)
			hex[i] = '0';
		return *this;
	}


	int HexNumber2::Parity() const {
		if (hex[31] >= '0' && hex[31] <= '9') {
			return ((int)hex[31] - 48) % 2;
		}
		switch (hex[31]) {
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
	HexNumber2& HexNumber2::operator<<=(const int a)//сдвиг влево
	{
		if (a < 0)
			throw std::exception("Invalid input");
		if (a == 0)
			return *this;
		if (a > (HexNumber2::MAX_LEN - length)) {//выходим за пределы 32 знаков слева
			HexNumber2 object;//пустой конструктор on
			*this = object;
			return *this;
		}
		for (int i = HexNumber2::MAX_LEN - length; i < HexNumber2::MAX_LEN; i++) {
			if ((i - a) > 0)
				hex[i - a] = hex[i];
		}
		for (int i = 0; i < a; i++) {//дополняем нулями справа
			hex[HexNumber2::MAX_LEN - i - 1] = '0';
		}
		length += a;
		if (length > 31)
			length = 31;
		return *this;

	}
	HexNumber2& HexNumber2::operator>>=(const int a)//cдвиг вправо
	{
		if (a < 0)
			throw std::exception("Invalid input");
		if (a == 0)
			return *this;
		if (a >= length) { //перемещаем всё число за разрядную сетку
			HexNumber2 object;//пустой конструктор on
			*this = object;
			return *this;
		}
		int stop = HexNumber2::MAX_LEN - length;
		for (int i = HexNumber2::MAX_LEN - 1; i >= stop; i--) {
			if ((i + a) < HexNumber2::MAX_LEN)
				hex[i + a] = hex[i];
			hex[i] = '0';
		}
		length -= a;
		return *this;
	}
	HexNumber2& HexNumber2::operator+() const
	{
		HexNumber2 res(*this);
		res.hex[0] = '0';

		return res;
	}
	HexNumber2& HexNumber2::operator+ (const HexNumber2& other) 
	{
		HexNumber2 add = other, result, first = *this;
		if (add.length == 1 && add.hex[1] == '0')//второй оператор просто 0
			return first;
		if (first.hex[0] == 'F')
			first.Convert();
		if (add.hex[0] == 'F')
			add.Convert();
		int t = 0;//перенос из младшего разряда
		for (int i = HexNumber2::MAX_LEN - 1; i > -1; i--) {
			int sum = CharToHex(first.hex[i]) + CharToHex(add.hex[i]);
			result.hex[i] = HexToChar((sum) % 0x10);
			t = 0;
			if (sum >>= 4)
				t = 1;
		}
		if (first.hex[0] == add.hex[0] && add.hex[0] != result.hex[0])//знаки слагаемых равны,но отличны от знака суммы-переполнение!
			throw std::exception("Overflow1");
		if (result.hex[0] == 'F') {
			try {
				result.Convert();
			}
			catch (std::exception& a) {
				throw std::exception("Overflow2");
			}
		}
		int k = 1;
		while (result.hex[k] == '0')
			k++;
		result.length = HexNumber2::MAX_LEN - k;
		if (!result.length)//значит, результат 0
			result.length = 1;
		return result;
	}

	HexNumber2& HexNumber2::operator-() const
	{
		HexNumber2 res(*this);
		if (getSign())
			res.hex[0] = (getSign()=='0') ? 'F' : '0';
		return res;
	}

	HexNumber2& HexNumber2::operator=(const HexNumber2& other)
	{
		if (this != &other) {
			length = other.length;
			std::copy(other.hex, other.hex + HexNumber2::MAX_LEN, hex);
		}
		return *this;
	}
	bool HexNumber2::operator>(const HexNumber2& other) const
	{
		if (hex[0] == other.hex[0]) {
			int l = length;
			if (other.length > length)
				l = other.length;
			char sgn = getSign();
			//HexNumber::MAX_LEN-l-позиция, начиная с которой сравниваем цифры
			for (int i = HexNumber2::MAX_LEN - l; i < HexNumber2::MAX_LEN; i++) {
				if (hex[i] > other.hex[i])
					return sgn == '0';
				else
					return sgn == 'F';
			}
		}
		else return hex[0] == '0';
	}

	bool HexNumber2::operator==(const HexNumber2& other) const
	{
		if (hex[0] != other.hex[0]) return false;
		else {
			int l = length;
			if (other.length > length)
				l = length;
			for (int i = HexNumber2::MAX_LEN - l; i < HexNumber2::MAX_LEN; i++)
				if (hex[i] != other.hex[i]) return false;
		}
		return true;
	}
	char HexNumber2::Compare(const HexNumber2& other) const
	{
		if (*this > other)
			return '>';
		else if (*this < other)
			return '<';
		else
			return '=';
	}
	std::ostream& operator<<(std::ostream& ostr, const HexNumber2& num)
	{
		if (num.getSign() == 'F')
			ostr << "-";
		int j = HexNumber2::MAX_LEN - num.length;
		std::copy(num.hex + j, num.hex + HexNumber2::MAX_LEN, std::ostream_iterator<char>(ostr, ""));
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, HexNumber2& num)
	{
		char* s = (char*)malloc(1), buf[35];
		int n = 0, l = 0;
		s[0] = '\0';
		do {
			n = scanf_s("%34[^\n]", buf, 35);
			if (n < 0)
			{
				free(s);
			}
			if (n > 0) {
				l += strlen(buf);
				s = (char*)realloc(s, l + 1);
				strcat_s(s, l + 1, buf);
			}
			if (n == 0)
				scanf_s("%*c");
		} while (n > 0);
		try {
			num.setN(s);
		}
		catch (std::exception& a) {
			istr.setstate(std::ios::failbit);
		}
		free(s);
		return istr;
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

}//namespace Prog3
