#include "C_DGLSolver.h"

CMyVector C_DGLSolver::ableitungen(CMyVector y, double x) {
    if(f_DGL_System != nullptr && f_DGL_nterOrdnung == nullptr) {
        return f_DGL_System(y, x);
    }
    else if (f_DGL_System == nullptr && f_DGL_nterOrdnung != nullptr) {
        int n = y.get_size();
        CMyVector dy(y);

        for (int i = 0; i < n - 1; i++) {
            dy[i] = y[i + 1];  // v(i+1)' = v(i+2)
        }

        dy[n - 1] = f_DGL_nterOrdnung(y, x);

        return dy;
    }
    else {
        std::cout << "Okay" << std::endl;
    }
    throw std::runtime_error("stop it");
}

//starting conditions and h input are missing

CMyVector C_DGLSolver::euler(double x_start, double x_end, int steps, CMyVector y_start) {
    double h = (x_end - x_start) / steps; 
    //double h = 0.3;
    double x = x_start;
    CMyVector y = y_start;
    for (int i = 0; i < steps && x <= x_end; i++) {
        CMyVector dy = ableitungen(y, x);
        //euler
        y = y + dy * h;
        x += h;

        //y.print();
        //dy.print();
        //std::cout << "--------" << std::endl;
    }
    //std::cout << "x: " << x <<  std::endl;

    return y;
}

CMyVector C_DGLSolver::heun(double x_start, double x_end, int steps, CMyVector y_start) {
    double h = (x_end - x_start) / steps;
    //double h = 0.3;
    double x = x_start;
    CMyVector y = y_start;

    for (int i = 0; i < steps && x <= x_end; i++) {
        CMyVector k1 = ableitungen(y, x);
        CMyVector k2 = ableitungen(y + k1 * h, x + h);
        //heun
        y = y + (k1 + k2) * (h / 2.0); 
        x += h;
    }

    return y;
}

/*
Mathematically, you can think of the vector returned as representing the instantaneous rates of change of each dependent variable at a given point. 
By evaluating the right-hand side functions for each dependent variable, you obtain a vector that describes how the variables are changing with respect to x at that point.
*/