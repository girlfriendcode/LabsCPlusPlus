//
// Created by mi on 28.09.2020.
//

#ifndef LAB1_2_LAB2_16_H
#define LAB1_2_LAB2_16_H
#endif //LAB1_2_LAB2_16_H

#include <cstring>

namespace Prog2 {
    struct Point {
        double x, y;

        explicit Point(double x0 = 0, double y0 = 0) : x(x0), y(y0) {};
    };

    class ChainLine {//цепная линия является чётной функцией
    private:
        double a;//параметр
    public:
        explicit ChainLine(double param = 1);//пустой конструктор с параметром=1 и центром(0,0)
        ChainLine &set_a(double param);

        double get_a() const;

        double get_Y(double x) const;

        double getLength(double x1, double x2) const;

        double getRadius(double x) const;

        double getArea(double x1, double x2) const;

        Point getCenter(double x) const;

        Point getProjection() const;
    };
}