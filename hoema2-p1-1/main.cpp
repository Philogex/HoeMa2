#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include "CMyVector.h"

double points[7][2] = {{-1.5, -0.8}, {-1, -0.6}, {-0.5, -0.9}, {0, -0.3}, {0.5, -0.8}, {1, 0.4}, {1.5, 0.3}};

double test_function1(const CMyVector& f) {
    if(f.get_size() != 3) {
        throw std::invalid_argument("Invalid function parameter");
    }
    return pow(f[0], 2) + 3*f[1] * pow(f[2], 2);
}

double test_function2(const CMyVector& f) {
    if(f.get_size() != 2) {
        throw std::invalid_argument("Invalid function parameter");
    }
    return sin(f[0] * f[1]) + sin(f[0]) + cos(f[1]);
}

double test_function3(const CMyVector& f) {
    if(f.get_size() != 3) {
        throw std::invalid_argument("Invalid function parameter");
    }
    return -(2 * pow(f[0], 2) - 2 * f[0] * f[1] + pow(f[1], 2) + pow(f[2], 2) - 2 * f[0] - 4 * f[2]);
}

double test_function4(const CMyVector& f) {
    if(f.get_size() != 2) {
        throw std::invalid_argument("Invalid function parameter");
    }
    return 2 * f[0] * sin(3 * pow(f[0], 2) * f[1]);
}

double test_function5(const CMyVector& f) {
    if(f.get_size() != 2) {
        throw std::invalid_argument("Invalid function parameter");
    }
    return 4 * pow(f[0], 3) + 4 * pow(f[1], 2) - 4 * f[0] * f[1] + 13;
}

double quadratic_deviation(const CMyVector& f) {
    double deviation = 0;
    for(int i = 0; i < static_cast<int>(sizeof(points) / sizeof(points[0])); i++) {
        double x = points[i][0];
        double y = points[i][1];
        double y_deviation = f[0]*x*x + f[1]*x + f[2];
        deviation += pow(y - y_deviation, 2);
    }
    return deviation;
}

int main() {
    //setting rounding
    std::cout << std::setprecision(6) << std::fixed;

    //init test vector
    double components1[] = {0.5, 1.5, 1};
    CMyVector test_vector1(components1, 3);

    //scalar mult test
    CMyVector test_vector2 = test_vector1 * 2;
    std::cout << std::endl << "scalar multiplication test" << std::endl;
    std::cout << std::endl << "scalar multiplication for test_vector1 * 2 = test_vector2" << std::endl;
    for(int i = 0; i < test_vector2.get_size(); i++) {
        std::cout << test_vector2[i] << std::endl;
    }

    //length test
    std::cout << std::endl << "length test" << std::endl;
    std::cout << std::endl << "length of test_vector1" << std::endl;
    std::cout << test_vector1.length() << std::endl;
    std::cout << "length test for test_vector2" << std::endl;
    std::cout << test_vector2.length() << std::endl;

    //gradient test
    std::cout << std::endl << "grandient test" << std::endl;
    std::cout << std::endl << "gradient for f1 in test_vector2" << std::endl;
    CMyVector test_vector3 = test_vector2.gradient(test_function1);
    for(int i = 0; i < test_vector3.get_size(); i++) {
        std::cout << test_vector3[i] << std::endl;
    }

    //maximize test
    std::cout << std::endl << "maximize test" << std::endl;
    std::cout << "maximize for [0.2, -2.1] with lambda=1.0 for f2" << std::endl;
    double components2[] = {0.2, -2.1};
    CMyVector test_vector4_1(components2, 2);
    CMyVector test_vector4_2 = test_vector4_1.maximize(test_function2);
    for(int i = 0; i < test_vector4_2.get_size(); i++) {
        std::cout << test_vector4_2[i] << std::endl;
    }

    std::cout << "maximize for [0, 0, 0] with lambda=0.1 for f3" << std::endl;
    double components3[] = {0, 0, 0};
    CMyVector test_vector5_1(components3, 3);
    CMyVector test_vector5_2 = test_vector5_1.maximize(test_function3, 0.1);
    for(int i = 0; i < test_vector5_2.get_size(); i++) {
        std::cout << test_vector5_2[i] << std::endl;
    }

    std::cout << "maximize for [1, 0] with lambda=0.25 for f4" << std::endl;
    double components4[] = {1, 0};
    CMyVector test_vector6_1(components4, 2);
    CMyVector test_vector6_2 = test_vector6_1.maximize(test_function4, 0.25);
    for(int i = 0; i < test_vector6_2.get_size(); i++) {
        std::cout << test_vector6_2[i] << std::endl;
    }

    //minimize test
    std::cout << std::endl << "minimize test" << std::endl;
    std::cout << "minimize for [0, 1] with lambda=0.5 for f5" << std::endl;
    double components5[] = {0, 1};
    CMyVector test_vector7_1(components5, 2);
    CMyVector test_vector7_2 = test_vector7_1.minimize(test_function5, 0.5);
    for(int i = 0; i < test_vector7_2.get_size(); i++) {
        std::cout << test_vector7_2[i] << std::endl;
    }

    //regression parabola test
    std::cout << std::endl << "regression parabola test" << std::endl;
    std::cout << "minimizing quadratic deviation in regard to given points starting at 0, 0, 0" << std::endl;
    double components6[] = {0, 0, 0};
    CMyVector test_vector8_1(components6, 3);
    CMyVector test_vector8_2 = test_vector8_1.minimize(quadratic_deviation);
    for(int i = 0; i < test_vector8_2.get_size(); i++) {
        std::cout << test_vector8_2[i] << std::endl;
    }

    system("pause");
    return 0;
}