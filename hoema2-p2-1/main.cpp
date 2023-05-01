#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include "CMyVector.h"
#include "CMyMatrix.h"

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

double quadratic_deviation(const CMyVector& f) {
    if(f.get_size() != 3) {
        throw std::invalid_argument("Invalid function parameter");
    }
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
    CMyVector test_vector8_2 = test_vector8_1.minimize(quadratic_deviation);
    test_vector8_2.print();

    //init test matrix
    CMyMatrix test_matrix1(5, 5);
    double** components7 = new double*[5];
    for (int i = 0; i < 5; i++) {
        components7[i] = new double[5];
        for (int j = 0; j < 5; j++) {
            components7[i][j] = i + j;
        }
    }

    //set matrix test
    std::cout << std::endl << "set_matrix test" << std::endl;
    test_matrix1.set_matrix(components7);
    test_matrix1.print();

    //copy constructor test
    std::cout << std::endl << "copy constructor test" << std::endl;
    CMyMatrix test_matrix2(test_matrix1);
    test_matrix2.print();

    //access operator [] test
    std::cout << std::endl << "access operator [] test" << std::endl;
    test_matrix2[2][3] = 3.33;
    test_matrix2.print();

    //assignment operator test
    std::cout << std::endl << "assignment operator test" << std::endl;
    test_matrix1 = test_matrix2;
    test_matrix1.print();

    //addition operator test
    std::cout << std::endl << "addition operator test" << std::endl;
    test_matrix1 = test_matrix1 + test_matrix2;
    test_matrix1.print();

    //subtraction operator test
    std::cout << std::endl << "subtraction operator test" << std::endl;
    test_matrix1 = test_matrix1 - test_matrix2;
    test_matrix1.print();

    //multiplication operator for two matrices
    std::cout << std::endl << "multiplication operator for two matrices" << std::endl;
    test_matrix1 = test_matrix1 * test_matrix2;
    test_matrix1.print();

    //multiplication operator for one matrix and a constant
    std::cout << std::endl << "multiplication operator for one matrix and a constant" << std::endl;
    test_matrix1 = test_matrix1 * 0.5;
    test_matrix1.print();

    //transposition of matrix test
    std::cout << std::endl << "transposition of matrix test" << std::endl;
    test_matrix2 = test_matrix1.transpose();
    test_matrix2.print();

    //determinant of matrix test
    std::cout << std::endl << "determinant of matrix test" << std::endl;
    CMyMatrix test_matrix3(2, 2);
    double* components9 = new double[2] {3, 7};
    double* components10 = new double[2] {1, -4};
    double** components8 = new double*[2] {components9, components10};
    test_matrix3.set_matrix(components8);
    //result should be -19
    std::cout << test_matrix3.determinant() << std::endl;

    //inverse of matrix test
    std::cout << std::endl << "inverse of matrix test" << std::endl;
    test_matrix1 = test_matrix3.inverse();
    test_matrix1.print();
    test_matrix3 = test_matrix3 * test_matrix1;
    test_matrix3.print();

    //jacobi matrix test
    std::cout << std::endl << "jacobi matrix test" << std::endl;
    CMyVector test_vector9(new double[4] {1, 2, 0, 3}, 4);
    CMyMatrix test_matrix4(3, 4);
    test_matrix4 = test_matrix4.jacobi(test_vector9, test_function6);
    test_matrix4.print();

    //newton root test
    std::cout << std::endl << "newton root test" << std::endl;
    CMyVector test_vector10(new double[2] {1, 1}, 2);
    CMyMatrix test_matrix5(2, 2);
    test_vector10 = test_matrix5.newton(test_vector10, test_function7);
    test_vector10.print();

    //prakt test 1
    std::cout << std::endl << "prakt test 1" << std::endl;
    CMyVector test_vector11(new double[3] {1, 2, 3}, 3);
    CMyMatrix test_matrix6(2, 3);
    test_matrix6 = test_matrix6.jacobi(test_vector11, test_function8);
    test_matrix6.print();

    //prakt test 2
    std::cout << std::endl << "prakt test 2" << std::endl;
    CMyVector test_vector12(new double[2] {-1, 0}, 2);
    CMyMatrix test_matrix7(2, 2);
    test_vector12 = test_matrix7.newton(test_vector12, test_function9);
    test_vector12.print();


    system("pause");
    return 0;
}