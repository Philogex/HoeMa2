#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include "CMyVector.h"
#include "C_DGLSolver.h"

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

//this return value is an actual vector in the usual sense. not the y values of my matrix, so i need to transpose it for input
CMyVector test_function6(const CMyVector& f) {
    if(f.get_size() != 4) {
        throw std::invalid_argument("Invalid function parameter");
    }
    CMyVector result(new double[3] {f[0] * f[1] * std::exp(f[2]), f[1] * f[2] * f[3], f[3]}, 3);
    return result;
}

//this return value is an actual vector in the usual sense. not the y values of my matrix, so i need to transpose it for input
CMyVector test_function7(const CMyVector& f) {
    if(f.get_size() != 2) {
        throw std::invalid_argument("Invalid function parameter");
    }
    CMyVector result(new double[2] {std::pow(f[0], 3) * std::pow(f[1], 3) - 2 * f[1], f[0] - 2}, 2);
    return result;
}

CMyVector test_function8(const CMyVector& f) {
    if(f.get_size() != 3) {
        throw std::invalid_argument("Invalid function parameter");
    }
    CMyVector result(new double[2] {4 * std::pow(f[0], 2) * f[1], 4  * std::pow(f[2], 2) + 4}, 2);
    return result;
}

CMyVector test_function9(const CMyVector& f) {
    if(f.get_size() != 2) {
        throw std::invalid_argument("Invalid function parameter");
    }
    CMyVector result(new double[2] {-std::pow(f[0], 2) * f[1] + 2 * f[0] + 2, -std::pow(f[1], 2) + 2 * f[0] - 2 * f[1] + 2}, 2);
    return result;
}

CMyVector test_function10(CMyVector y, double x) {
    if(y.get_size() != 2) {
        throw std::invalid_argument("Invalid function parameter");
    }
    CMyVector result(new double[2] {2 * y[1] - x * y[0], y[0] * y[1] - 2 * std::pow(x, 3)}, 2);
    return result;
}

double test_function11(CMyVector y, double x) {
    if(y.get_size() != 3) {
        throw std::invalid_argument("Invalid function parameter");
    }
    return 2 * x * y[1] * y[2] + 2 * std::pow(y[0], 2) * y[1];
}

double test_function12(CMyVector y, double x) {
    if(y.get_size() != 1) {
        throw std::invalid_argument("Invalid function parameter");
    }
    return -2 * x + y[0] - 2;
}

CMyVector test_function13(CMyVector y, double x) {
    if(y.get_size() != 2) {
        throw std::invalid_argument("Invalid function parameter");
    }
    CMyVector result(new double[2] {y[0] * (2 - y[1]), y[1] * (y[0] - 1)}, 2);
    return result;
}

double test_function14(CMyVector y, double x) {
    if(y.get_size() != 3) {
        throw std::invalid_argument("Invalid function parameter");
    }
    return 3 * x * std::pow(y[0], 2) * y[1] + std::pow(x, 4) * y[1] * y[2];
}

double test_function15(CMyVector y, double x) {
    if(y.get_size() != 2) {
        throw std::invalid_argument("Invalid function parameter");
    }
    return x * y[0] * (1 - y[0]);
}

double points_1[7][2] = {{-1.5, -0.8}, {-1, -0.6}, {-0.5, -0.9}, {0, -0.3}, {0.5, -0.8}, {1, 0.4}, {1.5, 0.3}};

double quadratic_deviation_1(const CMyVector& f) {
    if(f.get_size() != 3) {
        throw std::invalid_argument("Invalid function parameter");
    }
    double deviation = 0;
    for(int i = 0; i < static_cast<int>(sizeof(points_1) / sizeof(points_1[0])); i++) {
        double x = points_1[i][0];
        double y = points_1[i][1];
        double y_deviation = f[0]*x*x + f[1]*x + f[2];
        deviation += pow(y - y_deviation, 2);
    }
    return deviation;
}

double points_2[7][2] {{0, 0.015}, {1, 0.032}, {2, 0.066}, {3, 0.132}, {4, 0.239}, {5, 0.392}, {6, 0.571}};

double quadratic_deviation_2(const CMyVector& f) {
    if(f.get_size() != 3) {
        throw std::invalid_argument("Invalid function parameter");
    }
    double deviation = 0;
    for(int i = 0; i < static_cast<int>(sizeof(points_2) / sizeof(points_2[0])); i++) {
        double x = points_2[i][0];
        double y = points_2[i][1];
        double y_deviation = f[0]*x*x + f[1]*x + f[2];
        deviation += pow(y - y_deviation, 2);
    }
    return deviation;
}


int main() {
    //setting rounding
    std::cout << std::setprecision(6) << std::fixed;

    /*
    //init test vector
    double components1[] = {0.5, 1.5, 1};
    CMyVector test_vector1(components1, 3);

    //scalar mult test
    CMyVector test_vector2 = test_vector1 * 2;
    std::cout << std::endl << "scalar multiplication test" << std::endl;
    std::cout << std::endl << "scalar multiplication for test_vector1 * 2 = test_vector2" << std::endl;
    test_vector2.print();

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
    test_vector3.print();

    //maximize test
    std::cout << std::endl << "maximize test" << std::endl;
    std::cout << "maximize for [0.2, -2.1] with lambda=1.0 for f2" << std::endl;
    double components2[] = {0.2, -2.1};
    CMyVector test_vector4_1(components2, 2);
    CMyVector test_vector4_2 = test_vector4_1.maximize(test_function2);
    test_vector4_2.print();

    std::cout << "maximize for [0, 0, 0] with lambda=0.1 for f3" << std::endl;
    double components3[] = {0, 0, 0};
    CMyVector test_vector5_1(components3, 3);
    CMyVector test_vector5_2 = test_vector5_1.maximize(test_function3, 0.1);
    test_vector5_2.print();

    std::cout << "maximize for [1, 0] with lambda=0.25 for f4" << std::endl;
    double components4[] = {1, 0};
    CMyVector test_vector6_1(components4, 2);
    CMyVector test_vector6_2 = test_vector6_1.maximize(test_function4, 0.25);
    test_vector6_2.print();

    //minimize test
    std::cout << std::endl << "minimize test" << std::endl;
    std::cout << "minimize for [0, 1] with lambda=0.5 for f5" << std::endl;
    double components5[] = {0, 1};
    CMyVector test_vector7_1(components5, 2);
    CMyVector test_vector7_2 = test_vector7_1.minimize(test_function5, 0.5);
    test_vector7_2.print();

    //regression parabola test
    std::cout << std::endl << "regression parabola test" << std::endl;
    std::cout << "minimizing quadratic deviation in regard to given points starting at 0, 0, 0" << std::endl;
    double components6[] = {0, 0, 0};
    CMyVector test_vector8_1(components6, 3);
    CMyVector test_vector8_2 = test_vector8_1.minimize(quadratic_deviation_1);
    test_vector8_2.print();

    */

    //dgl_solver test
    std::cout << std::endl << "dgl_solver test" << std::endl;

    std::cout << "dgl_1" << std::endl;
    C_DGLSolver test_dgl1(test_function10);
    //start values for 4.1
    CMyVector test_vector9_1(new double[2] {0, 1}, 2);
    test_dgl1.ableitungen(test_vector9_1, 0).print();

    std::cout << "dgl_2" << std::endl;
    C_DGLSolver test_dgl2(test_function11);
    //start values for 4.2
    CMyVector test_vector9_2(new double[3] {1, -1, 2}, 3);
    test_dgl2.ableitungen(test_vector9_2, 1).print();

    //euler test
    std::cout << std::endl << "euler test" << std::endl;
    test_dgl1.euler(0, 2, 100, test_vector9_1).print();
    test_dgl2.euler(1, 2, 100, test_vector9_2).print();
    //difference to optimum
    for (int i : {10, 100, 1000, 10000}) {
        std::cout << "deviation for euler " << i << ": " << 0.5 - test_dgl2.euler(1, 2, i, test_vector9_2)[0] << std::endl;
    }

    //heun test
    std::cout << std::endl << "heun test" << std::endl;
    test_dgl1.heun(0, 2, 100, test_vector9_1).print();
    test_dgl2.heun(1, 2, 100, test_vector9_2).print();

    //difference to optimum
    for (int i : {10, 100, 1000, 10000}) {
        std::cout << "deviation for heun " << i << ": " << 0.5 - test_dgl2.heun(1, 2, i, test_vector9_2)[0] << std::endl;
    }

    //P3_1
    std::cout << std::endl << "P3_1" << std::endl;
    C_DGLSolver test_dgl3_1(test_function12);
    CMyVector test_vector10_1(new double[1] {2}, 1);
    test_dgl3_1.euler(3, 4, 1, test_vector10_1).print();
    test_dgl3_1.euler(3, 4, 2, test_vector10_1).print();
    test_dgl3_1.heun(3, 4, 1, test_vector10_1).print(); 

    //P3_2
    std::cout << std::endl << "P3_2" << std::endl;
    C_DGLSolver test_dgl3_2(test_function13);
    CMyVector test_vector10_2(new double[2] {0.9, 0.5}, 2);
    test_dgl3_2.euler(0, 0.6, 1, test_vector10_2).print();
    test_dgl3_2.euler(0, 0.6, 2, test_vector10_2).print();
    test_dgl3_2.heun(0, 0.3, 1, test_vector10_2).print();

    //P3_3
    std::cout << std::endl << "P3_3" << std::endl;
    C_DGLSolver test_dgl3_3(test_function14);
    CMyVector test_vector10_3(new double[3] {1, 2, 1}, 3);
    test_dgl3_3.euler(2, 2.1, 1, test_vector10_3).print();
    test_dgl3_3.euler(2, 2.2, 2, test_vector10_3).print();

    /*
    //P3_4
    eueler to approximate graph and minimize on resulting vector
    */

    system("pause");
    return 0;
}