#pragma once
#include <cmath>
#include "CMyVector.h"

//might have been a better idea to use templates, but i barely understand the math part, so i don't want to overdo it
class C_DGLSolver {
public:
    C_DGLSolver(CMyVector (*param) (CMyVector y, double x)) : f_DGL_System{param} {}
    C_DGLSolver(double (*param) (CMyVector y, double x)) : f_DGL_nterOrdnung{param}, firstOrder{false} {}
    CMyVector euler(double x_start, double x_end, int steps, CMyVector y_start);
    CMyVector heun(double x_start, double x_end, int steps, CMyVector y_start);

    //this is swapped to public for test cases
    CMyVector ableitungen(CMyVector y, double x);

private:
    CMyVector (*f_DGL_System) (CMyVector y, double x) = nullptr;
    double (*f_DGL_nterOrdnung) (CMyVector y, double x) = nullptr;
    bool firstOrder = true;
};