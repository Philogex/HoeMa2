#include "CLotto.h"

int* CLotto::s_ziehung() {
    int* result = new int[k]{0};
    m_cleanup.push_back(result);
    std::vector<bool> duplicates(n, false);
    int val;
    for(int i = 0; i < k; i++) {
        val = m_generator.wert(1, n);
        if(duplicates[val - 1] == false) {
            result[i] = val;
            duplicates[val - 1] = true;
        }
        else { i--; }
    }
    return result;
}

int CLotto::ziehung() {
    //naechsteffizienteste implementierung waere n (log n)^2 zeit mit weniger speicherbelegung
    int result = 0;
    std::vector<bool> duplicates(n, false);
    int val;
    for(int i = 0; i < k; i++) {
        val = m_generator.wert(1, n);
        if(duplicates[val - 1] == false) {
            if(m_tippmap[val - 1] == true) { result++; }
            duplicates[val - 1] = true;
        }
        else { i--; }
    }
    return result;
}