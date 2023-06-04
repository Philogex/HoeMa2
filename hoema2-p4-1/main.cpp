#include <iostream>
#include <fstream>   
#include <vector>
#include <complex>
#include "CKomplex.h"

constexpr double pi = 3.14159265358979323846;


std::vector<CKomplex> werte_einlesen(const std::string dateiname)
{
	int i, N, idx;
	double re, im;
	std::vector<CKomplex> werte;
		// File oeffnen
	std::ifstream fp;
	fp.open(dateiname);
		// Dimension einlesen
	fp >> N;
		// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0,0);
	for (i = 0; i<N; i++)
		werte[i] = null;
		// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re,im);
		werte[idx] = a;
	}
		// File schliessen
	fp.close();

	return werte;
}

//Zur Komprimierung der Daten kann beim Ausgeben ein ε ≥ 0 gew ̈ahlt werden. Es werdennur Eintrage abgespeichert, die großer als ε sind.
//muesste zu folgendem geaendert werden
//Zur Komprimierung der Daten kann beim Ausgeben ein ε > 0 gew ̈ahlt werden. Es werdennur Eintrage abgespeichert, die großer als ε sind.
void werte_ausgeben(const std::string dateiname, std::vector<CKomplex> werte, double epsilon = 0)
{
	int i;
	int N = werte.size();
		// File oeffnen
	std::ofstream fp;
	fp.open(dateiname);
		// Dimension in das File schreiben
	fp << N << std::endl;
		// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].get_re() << "\t" << werte[i].get_im() << std::endl;
	// File schliessen
	fp.close();
}

std::vector<CKomplex> fourier_transform(const std::vector<CKomplex>& data, bool invert = false) {
    int N = data.size();
    std::vector<CKomplex> result(N);

    const double norm = 1.0 / std::sqrt(N);

    for (int k = 0; k < N; k++) {
        double sum_re = 0;
        double sum_im = 0;

        for (int n = 0; n < N; n++) {
            CKomplex angle(2 * pi * k * n / N * (invert ? 1 : -1));
			sum_re += data[n].get_re() * angle.get_re() - data[n].get_im() * angle.get_im();
			sum_im += data[n].get_im() * angle.get_re() + data[n].get_re() * angle.get_im();
        }

        result[k] = CKomplex(sum_re, sum_im) * norm;
    }

    return result;
}

void print_complex_vector(std::vector<CKomplex> data) {
    for(size_t i = 0; i < data.size(); i++) {
        std::cout << i << "\t"; data[i].print();
    }
}

double deviation(std::vector<CKomplex> original, std::vector<CKomplex> comparison) {
	double deviation = 0;

    // Calculate the maximum deviation
    for (size_t i = 0; i < original.size(); ++i) {
        double cur_deviation = (original[i] - comparison[i]).abs();
        if (cur_deviation > deviation) {
            deviation = cur_deviation;
        }
    }

    return deviation;
}

int main() {
    std::cout << std::fixed << std::setprecision(10);

	/*
	std::vector<CKomplex> o_1 = werte_einlesen("Daten_original1.txt");
	std::vector<CKomplex> f_1 = fourier_transform(o_1);

	werte_ausgeben("1-0", f_1, 0);
	werte_ausgeben("1-0001", f_1, 0.001);
	werte_ausgeben("1-001", f_1, 0.01);
	werte_ausgeben("1-01", f_1, 0.1);
	werte_ausgeben("1-1", f_1, 1);

	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 0 bei datei 1: " << std::right << deviation(o_1, fourier_transform(werte_einlesen("1-0"), true)) << std::endl;
	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 0.001 bei datei 1: " << std::right << deviation(o_1, fourier_transform(werte_einlesen("1-0001"), true)) << std::endl;
	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 0.01 bei datei 1: " << std::right << deviation(o_1, fourier_transform(werte_einlesen("1-001"), true)) << std::endl;	
	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 0.1 bei datei 1: " << std::right << deviation(o_1, fourier_transform(werte_einlesen("1-01"), true)) << std::endl;
	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 1 bei datei 1: " << std::right << deviation(o_1, fourier_transform(werte_einlesen("1-1"), true)) << std::endl << std::endl;


	std::vector<CKomplex> o_2 = werte_einlesen("Daten_original2.txt");
	std::vector<CKomplex> f_2 = fourier_transform(o_2);

	werte_ausgeben("2-0", f_2, 0);
	werte_ausgeben("2-0001", f_2, 0.001);
	werte_ausgeben("2-001", f_2, 0.01);
	werte_ausgeben("2-01", f_2, 0.1);
	werte_ausgeben("2-1", f_2, 1);

	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 0 bei datei 2: " << std::right << deviation(o_2, fourier_transform(werte_einlesen("2-0"), true)) << std::endl;
	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 0.001 bei datei 2: " << std::right << deviation(o_2, fourier_transform(werte_einlesen("2-0001"), true)) << std::endl;
	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 0.01 bei datei 2: " << std::right << deviation(o_2, fourier_transform(werte_einlesen("2-001"), true)) << std::endl;	
	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 0.1 bei datei 2: " << std::right << deviation(o_2, fourier_transform(werte_einlesen("2-01"), true)) << std::endl;
	std::cout << std::setw(50) << std::left << "max. abweichung fuer epsilon = 1 bei datei 2: " << std::right << deviation(o_2, fourier_transform(werte_einlesen("2-1"), true)) << std::endl << std::endl;
	*/

	//std::vector<CKomplex> f_3 = fourier_transform(werte_einlesen("guitar.txt"));
	
	/*
	werte_ausgeben("guitar_f_1000.txt", f_3, 1000);
	werte_ausgeben("guitar_f_100.txt", f_3, 100);
	werte_ausgeben("guitar_f_10.txt", f_3, 10);
	werte_ausgeben("guitar_f_1.txt", f_3, 1);
	werte_ausgeben("guitar_f_0.txt", f_3, 0);

	werte_ausgeben("guitar_1000.txt", fourier_transform(werte_einlesen("guitar_f_1000.txt"), true));
	werte_ausgeben("guitar_100.txt", fourier_transform(werte_einlesen("guitar_f_100.txt"), true));
	werte_ausgeben("guitar_10.txt", fourier_transform(werte_einlesen("guitar_f_10.txt"), true));
	werte_ausgeben("guitar_1.txt", fourier_transform(werte_einlesen("guitar_f_1.txt"), true));
	werte_ausgeben("guitar_0.txt", fourier_transform(werte_einlesen("guitar_f_0.txt"), true));
	*/


	//std::vector<CKomplex> p4;
	//std::vector<std::vector<double>> input = {{0, 2}, {-2, 1}, {-3, -2}, {3, 2}};
	//std::vector<std::vector<double>> input = {{-2, 0}, {0, 0}, {1, 0}, {2, 0}, {2, 0}, {0, 0}};
	/*
	for(size_t i = 0; i < input.size(); i++) {
		CKomplex values(input[i][0], input[i][1]);
		p4.push_back(values);
	}
	*/
	/*
	p4.push_back(CKomplex(-3, 0));
	p4.push_back(CKomplex(2, 0));
	p4.push_back(CKomplex(1, -2));
	*/
	//print_complex_vector(fourier_transform(p4, true));

    system("pause");
    return 0;
}