#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>

class CMyVector {
public:
    CMyVector(double* components, int size) {
        m_size = size;
        m_components = new double[m_size];
        for (int i = 0; i < m_size; i++) {
            m_components[i] = components[i];
        }
    }
    
    ~CMyVector() {
        delete[] m_components;
    }
    
    CMyVector(const CMyVector& other) {
        m_size = other.m_size;
        m_components = new double[m_size];
        for (int i = 0; i < m_size; i++) {
            m_components[i] = other.m_components[i];
        }
    }
    
    CMyVector& operator=(const CMyVector& other);
    
    int get_size() const;

    double* get_components();
    
    void set_components(double* &components);
    
    double& operator[](int i);
    
    const double& operator[](int i) const;
    
    CMyVector operator+(const CMyVector& other) const;
    
    CMyVector operator-(const CMyVector& other) const;

    CMyVector operator*(const double& lambda) const;

    double dot_product(const CMyVector& other) const;

    CMyVector cross_product(const CMyVector& other) const;

    double length() const;

    CMyVector gradient(double (*function)(const CMyVector&)) const;

    CMyVector maximize(double (*function)(const CMyVector&), double lambda = 1.0) const;

    CMyVector minimize(double (*function)(const CMyVector&), double lambda = 1.0) const;

    void print();
    
private:
    double* m_components;
    int m_size;
};