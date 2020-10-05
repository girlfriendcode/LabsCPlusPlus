#include <iostream>
#include "lab2.16.cpp"

int main() {
    double a = 1;//параметр цепной линии  (начальный)
    int fl1 = 1;
    Prog2::ChainLine chain(a);
    while (fl1) {
        Prog2::Point point = chain.getProjection();//получаем точки подвеса
        std::cout << "Your line is:" << std::endl;
        std::cout << "Area :" << chain.getArea(point.y, point.x) << std::endl;
        std::cout << "Perimeter :" << chain.getLength(point.y, point.x) << std::endl;
        std::cout << "Enter x of point to find the  radius and the center :" << std::endl;
        double x_line;
        std::cin >> x_line;
        std::cout << "Radius: " << chain.getRadius(x_line) << std::endl;//радиус кривизны
        std::cout << "Center: [" << (chain.getCenter(x_line)).x << ";" << (chain.getCenter(x_line)).y << "]"
                  << std::endl;
        int fl2 = 1;
        std::cin.clear();
        while (fl2) {
            std::cout << "Enter x for calculating value of function f(x) or press crtl+z to quit" << std::endl;
            double x, y;
            std::cin >> x;
            fl2 = std::cin.good();
            if (!fl2)
                continue;
            try {
                y = chain.get_Y(x);
                std::cout << "f(x)= " << y << std::endl;
            }
            catch (std::exception &ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        std::cin.clear();
        std::cout << "Enter new parameter a or press crtl+z to quit: " << std::endl;
        std::cin >> a;
        if (std::cin.good()) {
            try {
                chain.set_a(a);
            }
            catch (std::exception &ex) {
                std::cout << ex.what() << std::endl;
            }
        } else
            fl1 = 0;

    }
    std::cout << "That's all!" << std::endl;
    return 0;
}
