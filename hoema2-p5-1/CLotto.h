#pragma once
#include <vector>
#include "CZufall.h"

class CLotto {
public:
    CLotto(int k, int n, int s) : k{k}, n{n} {
        //10/10 error handeling
        if(k > n) { std::cout << "k > n" << std::endl; system("pause"); exit(0); }
        m_generator.initialisiere((s < 0) ? time(NULL) : s);
        m_tippzettel = new int[k]{0};
        m_cleanup.push_back(m_tippzettel);
        m_tippmap.assign(n, false);
    }

    ~CLotto() {
        for(int* i : m_cleanup) {
            delete i;
        }
    }

    void set_tippzettel(int* param) {
        //std::copy(&param[0], &param[k], m_tippzettel); könnte optimisieren, aber ich muss die tippmap noch setzen, wodurch es keinen unterschied mehr macht
        m_tippmap.assign(n, false);
        for(int i = 0; i < k; i++) {
            m_tippzettel[i] = param[i];
            m_tippmap[param[i] - 1] = true;
        }
    }

    int* s_ziehung();

    int ziehung();


private:
    int* m_tippzettel;
    CZufall m_generator;

    int k;
    int n;
    std::vector<bool> m_tippmap;    //koennte durch unsigned long long int ersetzt werden, was jedoch begrenzten speicherplatz bietet, jedoch deutlich effizienter waere
    std::vector<int*> m_cleanup{nullptr};
};