#include <iostream>
#include "../Lab3_lib/HexNumber.h"
#include "../Lab3_lib/HexNumber.cpp"

void Prog3::dialog(HexNumber& a, HexNumber& b) {
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
int main() {
	Prog3::HexNumber a, b;
	int flag = 1;
	while (flag) {
		std::cout << "Enter first hexadecimal value" << std::endl;
		a.input(std::cin);
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = 0;
			continue;
		}
		std::cout << "Enter second hexadecimal value" << std::endl;
		b.input(std::cin);
		if (!std::cin.good()) {
			std::cout << "Wrong data" << std::endl;
			flag = 0;
			continue;
		}
		try {
			Prog3::HexNumber c(a.Add(b));
		    out(a, b, c, " + ");
		}
		catch (std::exception& b) {
			std::cout << b.what() << std::endl;
		}
		try {
			Prog3::HexNumber c(a.Sub(b));
			out(a, b, c, " - ");
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
