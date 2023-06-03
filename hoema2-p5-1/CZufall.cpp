#include "CZufall.h"

int CZufall::wert(int l, int h) {
    return std::rand() % (h - l + 1) + l;
}

void CZufall::initialisiere(int s) {
    std::srand(s);
}

void CZufall::test(int l, int h, int N) {
    int n = h - l + 1;
    int test[n]{0};

    for(int i = 0; i < N; i++) {
        test[wert(l, h) - l]++;
    }

    for(int i = 0; i < n; i++) {
        std::cout << i + l << ". Wert wurde " << test[i] << " Mal gezogen." << std::endl; 
    }
}

void CZufall::test_falsch(int l, int h, int N) {
    int n = h - l + 1;
    int test[n]{0};

    for(int i = 0; i < N; i++) {
        this->initialisiere(time(NULL));
        test[wert(l, h) - l]++;
    }

    for(int i = 0; i < n; i++) {
        std::cout << i + l << ". Wert wurde " << test[i] << " Mal gezogen." << std::endl; 
    }
}