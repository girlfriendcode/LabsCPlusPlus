#include <iostream>
#include "../Lab3_lib/HexNumber.h"
#include "../Lab3_lib/HexNumber.cpp"
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
