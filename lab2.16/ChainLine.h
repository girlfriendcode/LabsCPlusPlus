#pragma once
#include <cstring>
#include <iostream>
#include <tuple>
namespace Prog2 {

	class ChainLine {//цепная линия является чётной функцией
	private:
		double a;//параметр
		double x1;
		double x2;
	public:

		ChainLine();
		ChainLine(double param);
		ChainLine(double param, double p1);
		ChainLine(double param, double p1, double p2);

		ChainLine& set_a(double param);
		ChainLine& set_x2(double p2);
		ChainLine& set_x1(double p1);


		double get_x1()const;
		double get_x2()const;

		double get_a() const;

		double f(double x) const;

		double getLength(double x1, double x2) const;

		double getRadius(double x) const;

		double getArea(double x1, double x2) const;

		std::tuple<double, double> getCenter(double x) const;

	};
}

