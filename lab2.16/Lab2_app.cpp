
#include <iostream>
#include "..\Lab2_lib\ChainLine.h"
#include"..\Lab2_lib\ChainLine.cpp"
#include <tuple>

int main() {
    int fl1 = 1;
    double a, x2, x1;
    Prog2::ChainLine chain(1, -1, 1);
    while (fl1) {
        std::cout << "Your line is:" << std::endl;
        std::cout << "Parameter: " << chain.get_a() << std::endl;
        std::cout << "Suspension points are: " << chain.get_x1() << " ; " << chain.get_x2() << std::endl;
        std::cout << "Area :" << chain.getArea(chain.get_x1(), chain.get_x2()) << std::endl;
        std::cout << "Perimeter :" << chain.getLength(chain.get_x1(), chain.get_x2()) << std::endl;
        std::cout << "Enter x of point to find the  radius and the center :" << std::endl;
        double x_b;
        std::cin >> x_b;
        std::cout << "Radius: " << chain.getRadius(x_b) << std::endl;
        std::cout << "Center: x =" << std::get<0>(chain.getCenter(x_b)) << " ; y = " << std::get<1>(chain.getCenter(x_b))
            << std::endl;
        int fl2 = 1;
        std::cin.clear();
        while (fl2) {
            std::cout << "Enter x to calculate value y(x) or press crtl+z to quit: ";
            double x;
            double y;
            std::cin >> x;
            fl2 = std::cin.good();
            if (!fl2)
                continue;
            try {
                y = chain.f(x);
                std::cout << " y(x) = " << y << std::endl;
            }
            catch (std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        std::cin.clear();
        std::cout << " Enter new a and x2,x1 to continue or press crtl+z to quit" << std::endl;
        std::cin >> a >> x1 >> x2;
        if (std::cin.good()) {
            try {
                chain.set_a(a);
                chain.set_x2(x2);
                chain.set_x1(x1);
            }
            catch (std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else
            fl1 = 0;
    }
    std::cout << "Goodbye!\n";
    return 0;

}
