#include "CKomplex.h"

CKomplex CKomplex::operator+(const CKomplex &other) const {
    CKomplex result(this->re + other.get_re(), this->im + other.get_im());
    return result;
}

CKomplex CKomplex::operator-(const CKomplex &other) const {
    CKomplex result(this->re - other.get_re(), this->im - other.get_im());
    return result;
}

CKomplex CKomplex::operator*(const CKomplex &other) const {
    //CKomplex result(); most vexing parse error
    CKomplex result(this->re * other.get_re() - this->im * other.get_im(), this->re * other.get_im() + this->im * other.get_re());
    return result;
}

CKomplex CKomplex::operator/(const double &other) const {
    CKomplex result(this->re / other, this->im / other);
    return result;
}

CKomplex& CKomplex::operator=(const CKomplex& other) {
    this->re = other.get_re();
    this->im = other.get_im();
    return *this;
}

CKomplex CKomplex::operator*(const double other) {
    this->re = this->re * other;
    this->im = this->im * other;
    return *this;
}

double CKomplex::abs() {
    return std::sqrt(this->re * this->re + this->im * this->im);
}

void CKomplex::print() {
    std::cout << "\t" << re << "\t" << im << std::endl;
}