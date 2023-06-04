#include <iostream>
#include "CZufall.h"
#include "CLotto.h"

int monte_carlo(int r, int k, int n, int N, bool typ) {
    int r_correct = 0;
    CLotto s(k, n, 0);
    //Spieler 1
    if(typ) {
        int values[k];
        for(int i = 0; i < k; i++) {
            values[i] = i + 1;
        }
        s.set_tippzettel(values);
        for(int i = 0; i < N; i++) {
            if(s.ziehung() == r) { r_correct++; }
        }
    }
    //Spieler 2
    else {
        for(int i = 0; i < N; i++) {
            s.set_tippzettel(s.s_ziehung());
            if(s.ziehung() == r) { r_correct++; }
        }
    }
    return r_correct;
}

int main() {
    CZufall generator;

    //a
    //hier wird drei Mal der gleiche Seed verwendet, weshalb das gleiche Problem wie bei c) auftritt
    std::cout << "Test a): " << std::endl << std::endl;
    for(int i = 0; i < 3; i++) {
        generator.initialisiere(3);
        generator.test(3, 7, 10000);
        std::cout << std::endl;
    }

    //b
    //selbst wenn es erneut sicherheitstechnisch fragwuerdig ist, werden verschiedene Seeds fuer jeden durchlauf verwendet.
    std::cout << "Test b): " << std::endl << std::endl;
    for(int i = 0; i < 3; i++) {
        generator.initialisiere(i);
        generator.test(3, 7, 10000);
        std::cout << std::endl;
    }


    //c
    //einmalige Initialisierung mit der Zeit seit 2000 ist voellig legitim, wenn auch fuer die meisten System sicherheitstechnisch fragwuerdig. hier wird es jedoch drei Mal verwendet, weshalb die Verteilung sich wiederholt
    std::cout << "Test c): " << std::endl << std::endl;
    for(int i = 0; i < 3; i++) {
        generator.initialisiere(time(NULL));
        generator.test(3, 7, 10000);
        std::cout << std::endl;
    }

    
    //d
    //time laeuft in Sekunden, weshalb hier der Seed immer wieder zurueckgesetzt wird. Aus diesem Grund sollte 10000 Mal die gleiche Zahl gezogen werden
    std::cout << "Test d): " << std::endl << std::endl;
    generator.test_falsch(3, 7, 10000);

    system("pause");

    int r = 3;
    int k = 8;
    int n = 37;
    for(int N : {10, 100, 1000, 10000, 100000}) {
        std::cout << "r = " << r << ", k = " << k << ", n = " << n << ", N = " << N << std::endl;
        std::cout << "Spieler 1: " << std::endl;
        std::cout << static_cast<double>(monte_carlo(r, k, n, N, true))/N << std::endl;

        std::cout << "Spieler 2: " << std::endl;
        std::cout << static_cast<double>(monte_carlo(r, k, n, N, false))/N << std::endl;
    }

    system("pause");
    return 0;
}