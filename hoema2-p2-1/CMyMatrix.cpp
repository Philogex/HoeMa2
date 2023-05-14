#include <cmath>
#include "CMyMatrix.h"

//need to add integrity checks for matrix dimensions

int CMyMatrix::get_rows() const { 
    return m_rows; 

}
int CMyMatrix::get_cols() const { 
    return m_cols; 
}

void CMyMatrix::set_matrix(double** &rows) {
    for(int i = 0; i < m_rows; i++) {
        m_data[i]->set_components(rows[i]);
    }
}

CMyMatrix& CMyMatrix::operator=(const CMyMatrix& other) {
    if (this != &other) {
        delete[] m_data;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = new CMyVector*[m_rows];
        for (int i = 0; i < m_rows; i++) {
            m_data[i] = new CMyVector(*other.m_data[i]);
        }
    }
    return *this;
}

CMyVector& CMyMatrix::operator[](int i) {
    if (i < 0 || i >= m_rows) {
        throw std::out_of_range("Index out of bounds");
    }
    return *m_data[i];
}
    
const CMyVector& CMyMatrix::operator[](int i) const {
    if (i < 0 || i >= m_rows) {
        throw std::out_of_range("Index out of bounds");
    }
    return *m_data[i];
}

CMyMatrix CMyMatrix::operator+(const CMyMatrix& other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::out_of_range("Either Index out of Bounds");
    }
    CMyMatrix result(*this);
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            result[i][j] = result[i][j] + other[i][j];
        }
    }
    return result;
}

CMyMatrix CMyMatrix::operator-(const CMyMatrix& other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::out_of_range("Either Index out of Bounds");
    }
    CMyMatrix result(*this);
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            result[i][j] = result[i][j] - other[i][j];
        }
    }
    return result;
}

CMyMatrix CMyMatrix::operator*(const CMyMatrix& other) const {
    if (m_cols != other.m_rows) {
        throw std::invalid_argument("Dimensions are not compatible");
    }
    CMyMatrix result(m_rows, other.m_cols);
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < other.m_cols; j++) {
            double sum = 0;
            for (int k = 0; k < m_cols; k++) {
                sum += (*this)[i][k] * other[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

CMyMatrix CMyMatrix::operator*(const double& lambda) const {
    CMyMatrix result(*this);
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            result[i][j] = result[i][j] * lambda;
        }
    }
    return result;
}

CMyMatrix CMyMatrix::transpose() const {
    CMyMatrix result(m_cols, m_rows);
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            result[j][i] = (*this)[i][j];
        }
    }
    return result;
}

double CMyMatrix::determinant() const {
    if (m_rows != m_cols) {
        throw std::invalid_argument("Dimensions are not square");
    }

    CMyMatrix copy(*this);

    double det = 1.0;
    for (int i = 0; i < m_rows; i++) {
        //inaccuracy mitigation
        //find max row
        int max_row = i;
        double max_value = std::abs(copy[i][i]);
        for (int j = i + 1; j < m_rows; j++) {
            double abs_value = std::abs(copy[j][i]);
            if (abs_value > max_value) {
                max_row = j;
                max_value = abs_value;
            }
        }

        //swap rows and change det accordingly
        if (max_row != i) {
            std::swap(copy[i], copy[max_row]);    
            det *= -1;
        }

        //build steps
        for (int j = i + 1; j < m_rows; j++) {
            double factor = copy[j][i] / copy[i][i];
            for (int k = i + 1; k < m_cols; k++) {
                copy[j][k] -= factor * copy[i][k];
            }
        }

        //det = product of diagonal values
        det *= copy[i][i];
    }

    return det;
}

CMyMatrix CMyMatrix::inverse() const {
    if (m_rows != m_cols) {
        throw std::invalid_argument("Matrix is not square");
    }

    double det = this->determinant();

    if(round(det * 10e5) / 10e5 == 0) {
        throw std::invalid_argument("Matrix is not invertible");
    }

    CMyMatrix copy(*this);
    CMyMatrix inv(m_rows, m_cols);

    //init identity matrix
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            if(i == j) {
                inv[i][j] = 1;
            } else {
                inv[i][j] = 0;
            }
        }
    }

    // perform Gaussian elimination
    for (int i = 0; i < m_rows; i++) {

        //inaccuracy mitigation
        //find max row
        int pivot_row = i;
        double max_value = std::abs(copy[i][i]);
        for (int j = 0; j < m_rows; j++) {
            double abs_value = std::abs(copy[j][i]);
            if (abs_value > max_value) {
                pivot_row = j;
                max_value = abs_value;
            }
        }

        //swap max row with current
        if (pivot_row != i) {
            std::swap(copy[i], copy[pivot_row]);
            std::swap(inv[i], inv[pivot_row]);
        }

        //divide max value to reduce to 1
        double pivot = copy[i][i];
        for (int j = 0; j < m_cols; j++) {
            copy[i][j] /= pivot;
            inv[i][j] /= pivot;
        }

        //subtract rows below current row for 0 triangle / steps
        for (int j = i + 1; j < m_rows; j++) {
            double lambda = copy[j][i];
            for (int k = 0; k < m_cols; k++) {
                copy[j][k] -= lambda * copy[i][k];
                inv[j][k] -= lambda * inv[i][k];
            }
        }
    }

    //subtract rows above current row for 0 triangle
    for (int i = m_rows - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double lambda = copy[j][i];
            for (int k = 0; k < m_cols; k++) {
                copy[j][k] -= lambda * copy[i][k];
                inv[j][k] -= lambda * inv[i][k];
            }
        }
    }

    return inv;
}

//nach meinen bisherigen implementierung wuerde es mehr sinn machen, dass hier fuer die vector klasse zu implementieren

CMyMatrix CMyMatrix::jacobi(CMyVector x, CMyVector (*f)(const CMyVector &x)) const {
    //should be 1e-4, but is inaccurate
    const double h = 10e-8;
    CMyMatrix result(m_rows, m_cols);
    CMyVector f0 = f(x);

    for (int i = 0; i < m_cols; i++) {
        //add h to i-th component of input vector
        CMyVector xp = x;
        xp[i] += h;
        CMyVector f1 = f(xp);

        //calculate jacobian column by numerical differential
        for (int j = 0; j < m_rows; j++) {
            result[j][i] = (f1[j] - f0[j]) / h;
        }
    }

    return result;
}

//input object needs to fit jacobi (same requirement as jacobi itself)
//the entire function can be improved by solving the system of linear equations for the unknown x_{n+1}^{x_{n}}
CMyVector CMyMatrix::newton(CMyVector x, CMyVector (*f)(const CMyVector &x)) const {
    //renamed lambda to epsilon, because my sister told me to
    const double epsilon = 10e-8;
    const int max_iterations = 50;
    const int size = x.get_size();
    int iteration = 0;
    CMyMatrix delta(size, size);
    delta[0][0] = 1;

    while (iteration < max_iterations && delta[0].length() >= epsilon) {
        //not very pretty, but i can't do much more bc of my current data structure
        CMyMatrix fx(1, size);
        fx[0] = f(x);
        fx = fx.transpose();
        CMyMatrix correction(this->jacobi(x, f));
        correction = correction.inverse();

        //same problem here as mentioned above. if i need to keep using this code i will rewrite large parts of my impelementation to increase usability
        delta = correction * fx;
        delta = delta.transpose();
        x = x - delta[0];

        iteration++;
    }

    return x;
}

void CMyMatrix::print() const {
    const int num_length = 14;
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            std::cout << std::setw(num_length) << (*this)[i][j] << " | ";
        }
        std::cout 
            << std::endl 
            << std::string((num_length + 3) * m_cols - 1, '-')
            << std::endl;
    }
    std::cout << std::endl;
}