//
// Created by mi on 28.09.2020.
//

#include "lab2.16.h"
#include <iostream>
#include <cmath>

namespace Prog2 {
    //при задании цепной линии параметр a!=0
    ChainLine::ChainLine(double param) {
        if (param == 0)
            std::cerr << "Invalid param a!\n";
        a = param;
    }

    ChainLine &ChainLine::set_a(double param) {
        if (param == 0)
            std::cerr << "Invalid param a!\n";
        a = param;
        return *this;
    }

    double ChainLine::get_Y(double x) const {
        return a * cosh(x / a);
    }

    double ChainLine::get_a() const {
        return a;
    }

    double ChainLine::getRadius(double x) const {
        return a * cosh(x / a) * cosh(x / a);
    }

    double ChainLine::getLength(double x1, double x2) const {
        return a * (sinh(x2 / a) - sinh(x1 / a));
    }

    double ChainLine::getArea(double x1, double x2) const {
        return a * a * (sinh(x2 / a) - sinh(x1 / a));
    }

    Point ChainLine::getCenter(double x) const {
        double y = get_Y(x);//какая-то точка кривой
        double y1 = sinh(x / a);//первая производная
        double y2 = get_Y(x) / (a * a);//вторая производная
        Point result;
        result.x = x - (y1 * (y1 * y1 + 1) / y2);
        result.y = y + ((y1 * y1 + 1) / y2);
        return result;
    }

    Point ChainLine::getProjection() const { //функция
        Point result;
        double x1, x2;
        std::cout << "Enter suspension abscesses x1 and x2: " << std::endl;
        std::cin >> x1 >> x2;
        if (x2 > x1) {
            result.x = x2;
            result.y = x1;
        } else {
            result.x = x1;
            result.y = x2;
        }
        return result;
    }


}
