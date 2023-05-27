#pragma once
#include <cmath>
#include <iostream>
#include <iomanip>

class CKomplex {
public:
    CKomplex() : re{0}, im{0} {}
    CKomplex(double a, double b) : re{a}, im{b} {}
    CKomplex(double phi) : re{std::cos(phi)}, im{std::sin(phi)} {}

    double get_re() const { return re; };
    double get_im() const { return im; };


    CKomplex operator+(const CKomplex &other) const;

    //optional
    CKomplex operator-(const CKomplex &other) const;

    CKomplex operator*(const CKomplex &other) const;

    //optional
    CKomplex operator/(const double &other) const;

    //optional
    CKomplex& operator=(const CKomplex& other);

    //optional
    CKomplex operator*(const double other);

    double abs();

    void print();

private:
    double re;
    double im;
};