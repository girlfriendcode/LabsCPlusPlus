#include <iostream>
#include "../Lab3_2_lib/HexNumber.h"
#include "../Lab3_2_lib/HexNumber.cpp"

void Prog3::dialog(HexNumber2& a, HexNumber2& b) {
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
				a>>=r;
			}
			catch (std::exception& b) {
				std::cout << b.what() << std::endl;
				continue;
			}
			std::cout << a << std::endl;
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
				a<<=r;
			}
			catch (std::exception& b) {
				std::cout << b.what() << std::endl;
				continue;
			}
			std::cout<< a << std::endl;
			break;
		case 3:
			std::cout << a;
			std::cout << " " << a.Compare(b) << " ";
			std::cout << b;
			std::cout << std::endl;
			break;
		case 4:
			if (!a.Parity()) {
				std::cout << a ;
				std::cout << " is an even number" << std::endl;
			}
			else {
				std::cout << a ;
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

int main() {
	Prog3::HexNumber2 a, b;
	int flag = 1;
	while (flag) {
		std::cout << "Enter first hexadecimal value" << std::endl;
		std::cin>> a;
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = 0;
			continue;
		}
		std::cout << "Enter second hexadecimal value" << std::endl;
		std::cin>> b;
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = 0;
			continue;
		}
		try {
			Prog3::HexNumber2 c=a+b;
			if (b.getSign() == 'F')
				std::cout << a << " + (" << b << ") = " << c << std::endl;
			else
				std::cout << a << " + " << b << " = " << c << std::endl;
		}
		catch (std::exception& b) {
			std::cout << b.what() << std::endl;
		}
		try {
			Prog3::HexNumber2 c=a-b;
			if (b.getSign() == 'F')
				std::cout << a << " - (" << b << ") = " << c << std::endl;
			else
				std::cout << a << " - " << b << " = " << c << std::endl;
		}
		catch (std::exception& b) {
			std::cout << b.what() << std::endl;
		}
		dialog(a, b);
		std::cout << "Press 0 if you want to exit or any other number to continue" << std::endl;
		std::cin >> flag;
		scanf_s("%*c");
	}
}
