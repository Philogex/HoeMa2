#include "CMyVector.h"
#include <cmath>

int CMyVector::get_size() const {
    return m_size;
}

double& CMyVector::operator[](int i) {
    return m_components[i];
}

const double& CMyVector::operator[](int i) const {
    return m_components[i];
}

CMyVector& CMyVector::operator=(const CMyVector& other) {
    if (this != &other) {
        delete[] m_components;
        m_size = other.m_size;
        m_components = new double[m_size];
        for (int i = 0; i < m_size; i++) {
            m_components[i] = other.m_components[i];
        }
    }
    return *this;
}

CMyVector CMyVector::operator+(const CMyVector& other) const {
    if (m_size != other.m_size) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    CMyVector result(m_components, m_size);
    for (int i = 0; i < m_size; i++) {
        result[i] += other[i];
    }
    return result;
}


CMyVector CMyVector::operator-(const CMyVector& other) const {
    if (m_size != other.m_size) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    CMyVector result(m_components, m_size);
    for (int i = 0; i < m_size; i++) {
        result[i] -= other[i];
    }
    return result;
}

CMyVector CMyVector::operator*(const double& lambda) const {
    CMyVector result(m_components, m_size);
    for (int i = 0; i < m_size; i++) {
        result[i] *= lambda;
    }
    return result;
}

double CMyVector::dot_product(const CMyVector& other) const {
    if (m_size != other.m_size) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    double result = 0;
    for (int i = 0; i < m_size; i++) {
        result += m_components[i] * other[i];
    }
    return result;
}

CMyVector CMyVector::cross_product(const CMyVector& other) const {
    if (m_size != other.m_size) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    double result[m_size] = {0};
    for (int i = 0; i < m_size; i++) {
        result[i] += m_components[(i + 1) % m_size] * other[(i + 2) % m_size] - m_components[(i + 2) % m_size] * other[(i + 1) % m_size];
    }
    return CMyVector(result, m_size);
}

double CMyVector::length() const {
    double result = 0;
    for(int i = 0; i < m_size; i++) {
        result += std::pow(m_components[i], 2);
    }
    return sqrt(result);
}

CMyVector CMyVector::gradient(double (*function)(const CMyVector&)) const {
    const double h = 1e-8;
    CMyVector result(m_components, m_size);

    for (int i = 0; i < m_size; i++) {
        CMyVector x_plus_h = *this;
        x_plus_h.m_components[i] += h;

        double fx = function(*this);
        double fx_plus_h = function(x_plus_h);

        result[i] = (fx_plus_h - fx) / h;
    }

    return result;
}

CMyVector CMyVector::maximize(double (*function)(const CMyVector&), double lambda) const {
    double acc = 1e-5;
    CMyVector result(m_components, m_size);
    CMyVector grad_f = result;
    double x0 = function(result);
    double x1;
    
    for(int i = 0; i < 25; i++) {
        grad_f = result.gradient(function);
        CMyVector step = result + grad_f * lambda;
        //std::cout << "step " << i << " for f = (" << step.m_components[0] << "; " << step.m_components[1] << ")" << std::endl;
        x1 = function(step);
        
        if (x1 <= x0) { lambda /= 2; }
        else {
            double test_lambda = 2 * lambda;
            CMyVector test_step = result + grad_f * test_lambda;
            double test_x1 = function(test_step);
            if (test_x1 > x1) {
                lambda = test_lambda;
                x0 = test_x1;
                result = test_step;
            }
            else {
                x0 = x1;
                result = step;
            }
        }
        if(grad_f.length() <= acc) { break; }
    }

    return result;
}

CMyVector CMyVector::minimize(double (*function)(const CMyVector&), double lambda) const {
    double acc = 1e-5;
    CMyVector result(m_components, m_size);
    CMyVector grad_f = result;
    double x0 = function(result);
    double x1;
    
    for(int i = 0; i < 25; i++) {
        grad_f = result.gradient(function);
        CMyVector step = result - grad_f * lambda;
        //std::cout << "step " << i << " for f = (" << step.m_components[0] << "; " << step.m_components[1] << ")" << std::endl;
        x1 = function(step);
        if (x1 >= x0) { lambda /= 2; }
        else {
            double test_lambda = 2 * lambda;
            CMyVector test_step = result - grad_f * test_lambda;
            double test_x1 = function(test_step);
            if (test_x1 < x1) {
                lambda = test_lambda;
                x0 = test_x1;
                result = test_step;
            }
            else {
                x0 = x1;
                result = step;
            }
        }
        if(grad_f.length() <= acc) { break; }
    }

    return result;
}