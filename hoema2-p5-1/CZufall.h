#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>

class CZufall {
public:
    int wert(int l, int h);
    void initialisiere(int s);
    void test(int a, int b, int N);
    void test_falsch(int a, int b, int N);
};