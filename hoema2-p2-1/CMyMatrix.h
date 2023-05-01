#pragma once
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include "CMyVector.h"


class CMyMatrix {
public:
    CMyMatrix(int rows, int cols) {
        m_rows = rows;
        m_cols = cols;
        m_data = new CMyVector*[rows];
        for (int i = 0; i < rows; i++) {
            m_data[i] = new CMyVector(new double[cols] {0}, cols);
        }
    }
    
    ~CMyMatrix() {
        delete[] m_data;
    }
    
    CMyMatrix(const CMyMatrix& other) {
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = new CMyVector*[m_rows];
        for (int i = 0; i < m_rows; i++) {
            m_data[i] = new CMyVector(*other.m_data[i]);
        }
    }
    
    int get_rows() const;

    int get_cols() const;

    void set_matrix(double** &rows);

    CMyMatrix& operator=(const CMyMatrix& other);
    
    CMyVector& operator[](int i);
    
    const CMyVector& operator[](int i) const;
    
    CMyMatrix operator+(const CMyMatrix& other) const;
    
    CMyMatrix operator-(const CMyMatrix& other) const;
    
    CMyMatrix operator*(const CMyMatrix& other) const;

    CMyMatrix operator*(const double& lambda) const;

    CMyMatrix transpose() const;

    double determinant() const;

    CMyMatrix inverse() const;

    void print() const;

    CMyMatrix jacobi(CMyVector x, CMyVector (*function)(const CMyVector &x)) const;

    CMyVector newton(CMyVector x, CMyVector (*function)(const CMyVector &x)) const;

private:
    CMyVector** m_data;
    int m_rows;
    int m_cols;
};