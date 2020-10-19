#include "pch.h"
#include "HexNumber.h"
#include <iostream>
#include <string.h>

namespace Prog3 {
	HexNumber::HexNumber() //пустой конструктор
	{
		for (int i = 0; i < maxLen; i++)
			hex[i] = '0';
		length = 1;
	}

	HexNumber::HexNumber(char* str)//инициализирующий строкой конструктор
	{
		try {
			setN(str);
		}
		catch (std::exception& a) {
			throw std::exception("Wrong data");
		}
	}

	HexNumber::HexNumber(const long int a)
	{
		int a2 = a;
		if (a < 0) {
			hex[0] = 'F';
			a2 = -a;
		}
		else
			hex[0] = '0';
		int i = maxLen - 1;
		for (; a2; i--) {
			hex[i] = HexToChar(a2 & 0xf);
			a2 >>= 4;
		}
		for (int j = 1; j <= i; j++)
			hex[j] = '0';
		length = maxLen - i - 1;
		if (!length)
			length = 1;
	}

	char HexNumber::getSign() const
	{
		return hex[0];
	}

	char HexNumber::getElement(int i) const
	{
		return hex[i];
	}

	HexNumber::HexNumber(const HexNumber& number) {
		for (int i = 0; i < maxLen; i++) {
			hex[i] = number.hex[i];
		}
		length = number.length;
	}

	HexNumber& HexNumber::setN(char* str) {
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
		int ll = maxLen - leng + i;//место, с которого начинаем вводить число в массив
		if (ll < 1)
			ll = 1;
		for (int j = 1; j < ll; j++)// заполняем массив нулями до значащих цифр
			hex[j] = '0';
		length = ((leng - i) > 31) ? 31 : leng - i;
		for (int j = i; j < leng && ll < maxLen; j++, ll++) {
			str[j] = upper(str[j]); //проверка регистра
			if ((str[j] < '0' || ('9' < str[j] && str[j] < 'A') || 'F' < str[j]))//проверка попадания символа в диапазон шестнадцатиричных цифр
				throw std::exception("Invalid symbol");
			hex[ll] = str[j];
		}
		if (leng - i > 31)
			std::cout << "Only first 31 digits will be read" << std::endl;
		if ((hex[0] == 'F' && length == 1 && hex[maxLen - 1] == '0') || !length) {
			HexNumber c;
			*this = c;
		}
		return *this;
	}

	const HexNumber HexNumber::Add(const HexNumber& num) {
		HexNumber add = num, result, first = *this;
		if (add.length == 1 && add.hex[1] == '0')//второй оператор просто 0
			return first;
		if (first.hex[0] == 'F')
			first.Convert();
		if (add.hex[0] == 'F')
			add.Convert();
		int t = 0;//перенос из младшего разряда
		for (int i = maxLen - 1; i > -1; i--) {
			int sum = CharToHex(first.hex[i]) + CharToHex(add.hex[i]);
			result.hex[i] = HexToChar((sum) % 0x10);
			t = 0;
			if (sum >>= 4)
				t = 1;
		}
		if (first.hex[0] == add.hex[0] && add.hex[0] != result.hex[0])//знаки слагаемых равны,но отличны от знака суммы-переполнение!
			throw std::exception("Overflow");
		if (result.hex[0] == 'F') {
			try {
				result.Convert();
			}
			catch (std::exception& a) {
				throw std::exception("Overflow");
			}
		}
		int k = 1;
		while (result.hex[k] == '0')
			k++;
		result.length = maxLen - k;
		if (!result.length)//значит, результат 0
			result.length = 1;
		return result;
	}

	const HexNumber HexNumber::Sub(const HexNumber& num)
	{
		HexNumber sub = num, result;
		if (sub.hex[0] == '0')//положительное число
			sub.hex[0] = 'F';
		else
			sub.hex[0] = '0';
		try {
			result = Add(sub);
		}
		catch (std::exception& a) {
			throw std::exception("Overflow");
		}
		return result;
	}

	HexNumber& HexNumber::moveRight(int a)
	{
		if (a < 0)
			throw std::exception("Invalid input");
		if (a == 0)
			return *this;
		if (a >= length) { //перемещаем всё число за разрядную сетку
			HexNumber object;//пустой конструктор on
			*this = object;
			return *this;
		}
		int stop = maxLen - length;
		for (int i = maxLen - 1; i >= stop; i--) {
			if ((i + a) < maxLen)
				hex[i + a] = hex[i];
			hex[i] = '0';
		}
		length -= a;
		return *this;
	}
	HexNumber& HexNumber::moveLeft(int a) {
		if (a < 0)
			throw std::exception("Invalid input");
		if (a == 0)
			return *this;
		if (a > (maxLen - length)) {//выходим за пределы 32 знаков
			HexNumber object;//пустой конструктор on
			*this = object;
			return *this;
		}
		for (int i = maxLen - length; i < maxLen; i++) {
			if ((i - a) > 0)
				hex[i - a] = hex[i];
		}
		for (int i = 0; i < a; i++) {//дополняем нулями справа
			hex[maxLen - i - 1] = '0';
		}
		length += a;
		if (length > 31)
			length = 31;
		return *this;
	}

	std::ostream& HexNumber::output(std::ostream& o)
	{
		if (hex[0] == 'F')
			o << "-";
		//пошли ненулевые элементы
		for (int j = maxLen - length;j < maxLen; j++) {
			o << hex[j];
		}
		return o;
	}

	std::istream& HexNumber::input(std::istream& i)
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
			setN(s);
		}
		catch (std::exception& a) {
			i.setstate(std::ios::failbit);
		}
		free(s);
		return i;
	}

	HexNumber& HexNumber::Convert()//перевод в допкод с добавлением единицы для отрицательных чисел
	{
		for (int i = 1; i < maxLen; i++) {
			int n = 0xF - CharToHex(hex[i]);
			hex[i] = HexToChar(n);
		}
		int l = maxLen - 1;
		while (l > 0 && hex[l] == 'F')//поиск места для добавления единицы
			l--;
		if (l == 0)
			throw std::exception("Overflow");
		int k = CharToHex(hex[l] + 1);
		hex[l] = HexToChar(k);
		for (int i = l + 1; i < maxLen; i++)
			hex[i] = '0';
		return *this;
	}

	char HexNumber::Compare(const HexNumber& num)
	{
		if (hex[0] < num.hex[0])//проверяем знаки
			return '>';
		if (hex[0] > num.hex[0])
			return '<';
		int l = length;
		if (num.length > length)
			l = num.length;
		char sgn = getSign();
		//maxLen-l-позиция, начиная с которой сравниваем цифры
		for (int i = maxLen - l; i < maxLen; i++) {
			if (hex[i] > num.getElement(i)) {
				if (sgn == '0')
					return '>';
				else
					return '<';
			}
			if (hex[i] < num.hex[i]) {
				if (sgn == '0')
					return '<';
				else
					return '>';
			}
		}
		return '=';
	}

	int HexNumber::Parity() {
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

	char upper(const char a) {
		switch (a) {
		case 'a':return 'A';
		case 'b':return 'B';
		case 'c':return 'C';
		case 'd':return 'D';
		case 'e':return 'E';
		case 'f':return 'F';
		}
		return a;
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
  
	void dialog(HexNumber& a, HexNumber& b) {
		int k = 0;
		while (k != 5) {
			std::cout << "1) Move first/actual operand to the right" << std::endl << "2) Move first/actual operand to the left" << std::endl << "3) Compare operands (first/actual with the second)" << std::endl << "4) Check parity of first/actual operand" << std::endl << "5) Exit" << std::endl;
			std::cin >> k;
			if (!std::cin.good()) {
				std::cout << "Invalid input" << std::endl;
				k = 5;
				continue;
			}
			switch (k) {
			case 1:
				int r;
				std::cout << "Enter number of digits" << std::endl;
				std::cin >> r;
				if (!std::cin.good()) {
					std::cout << "Invalid input" << std::endl;
					k = 5;
					continue;
				}
				try {
					a.moveRight(r);
				}
				catch (std::exception& b) {
					std::cout << b.what() << std::endl;
					continue;
				}
				a.output(std::cout);
				std::cout << std::endl;
				break;
			case 2:
				std::cout << "Enter number of digits" << std::endl;
				std::cin >> r;
				if (!std::cin.good()) {
					std::cout << "Invalid input" << std::endl;
					k = 5;
					continue;
				}
				try {
					a.moveLeft(r);
				}
				catch (std::exception& b) {
					std::cout << b.what() << std::endl;
					continue;
				}
				a.output(std::cout);
				std::cout << std::endl;
				break;
			case 3:
				a.output(std::cout);
				std::cout << " " << a.Compare(b) << " ";
				b.output(std::cout);
				std::cout << std::endl;
				break;
			case 4:
				if (!a.Parity()) {
					a.output(std::cout);
					std::cout << " is an even number" << std::endl;
				}
				else {
					a.output(std::cout);
					std::cout << " isn't an even number" << std::endl;
				}
				break;
			case 5:
				continue;
			default:
				std::cout << "You are wrong, repeat please" << std::endl;
			}
		}
	}
  
	void out(HexNumber& a, HexNumber& b, HexNumber& c, const char* msg) {
		if (b.getSign() == 'F') {
			a.output(std::cout);
			std::cout << msg << "(";
			b.output(std::cout);
			std::cout << ") = ";
			c.output(std::cout);
			std::cout << std::endl;
		}
		else {
			a.output(std::cout);
			std::cout << msg;
			b.output(std::cout);
			std::cout << " = ";
			c.output(std::cout);
			std::cout << std::endl;
		}
	}
  
}
