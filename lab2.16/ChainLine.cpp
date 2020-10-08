#include "pch.h"
#include "ChainLine.h"
#include <iostream>
#include <cmath>

namespace Prog2 {

    ChainLine::ChainLine(double param, double p1, double p2) {// по умолчанию: (1,-1,1)
        if (param == 0)
            throw std::exception("Invalid parameter a!");
        a = param;
        x2 = p2;
        x1 = p1;
    }

    ChainLine::ChainLine(double param, double p1) {
        if (param == 0)
            throw std::exception("Invalid parameter a!");
        a = param;
        x1 = p1;
        x2 = 1;
        
    }

    ChainLine::ChainLine(double param) : ChainLine(a, -1) {
        if (param == 0)
            throw std::exception("Invalid parameter a!");
        a = param;
    }

    ChainLine::ChainLine() : ChainLine(1) {
    }

    ChainLine& ChainLine::set_x1(double p1) {
        x1 = p1;
        return *this;
    }

    ChainLine& ChainLine::set_x2(double p2) {
        x2 = p2;
        return *this;
    }

    ChainLine& ChainLine::set_a(double param) {
        if (param == 0)
            throw std::exception("Invalid param a!");
        a = param;
        return *this;
    }

    double ChainLine::f(double x) const {

        return a * cosh(x / a);
    }

    double ChainLine::get_a() const {
        return a;
    }

    double ChainLine::get_x1() const {
        return x1;
    }

    double ChainLine::get_x2() const {
        return x2;
    }

    double ChainLine::getRadius(double x) const {

        return a * cosh(x / a) * cosh(x / a);
    }

    double ChainLine::getLength(double x1, double x2) const {

        return a * abs((sinh(x2 / a) - sinh(x1 / a)));
    }

    double ChainLine::getArea(double x1, double x2) const {

        return a * a * abs((sinh(x2 / a) - sinh(x1 / a)));
    }

    std::tuple<double, double> ChainLine::getCenter(double x) const { //центр кривизны
        double y = f(x);//какая-то точка кривой
        double y1 = sinh((x) / a);//первая производная
        double y2 = cosh((x) / a) / a;//вторая производная
        double center_x = x - (y1 * (y1 * y1 + 1) / y2);
        double center_y = y + ((y1 * y1 + 1) / y2);
        return std::make_tuple(center_x, center_y);
    }

}
