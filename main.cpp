/*
1. obliczyc f(x) = [1 - exp(-x)]/x
2. zbadaj jak zmieniają się błędy względne w zależności od x
    a) wykonać rysunek przedstawiający zależność log dziesiętnego z bezwzgl.
    wart. bł wzlg. od logarytmu dziesiętnego z x log(|błąd log(x)|)
    b) z wykresu odczytać zakres zmiennej x w którym błąd pozostaje w zakresie
    błędu reprezentacji, oraz zakres x w którym błąd jest większy
    c) wyjaśnij przyczynę obserwowantych zmian błędów
3. zaproponuj alternatywny sposób obliczana f(x) w miejscach w których błąd jest
duży
4. zmodywikować program tak aby błąd względny został zredukowany do błędu
reprezentacji (czyli do dokładności maszynowej) dla dowolnego x

*zastosować zmienne podwójnej precyzji
**użyc GNUPLOT do zrobienia rysunku
*/

#include <iostream>
#include "math.h"
#include <fstream>

using namespace std;

double funkcja(double x){
    return (1-exp(-x))/x;
}

double funkcjaUlepszona(double x) {
    double wynik = 1;
    double znak = -1;
    double krok = 1;

    for (int i = 2; i < 20; ++i){
        krok = krok * (x / i);
        wynik += znak * krok;
        znak = -znak;
    }

    return wynik;
}

int main() {
    double x, wynik, wynikFile, wynikLog, logFile;
    ifstream fileX;
    ifstream fileFun;
    ifstream fileLog;
    ofstream wyniki;
    ofstream wyniki_plus_X;
    wyniki.open("C:\\Users\\bartek\\CLionProjects\\MO_lab2\\wyniki");
    fileX.open("C:\\Users\\bartek\\CLionProjects\\MO_lab2\\sourceX");
    fileFun.open("C:\\Users\\bartek\\CLionProjects\\MO_lab2\\sourceFunction");
    fileLog.open("C:\\Users\\bartek\\CLionProjects\\MO_lab2\\sourceLog");
    wyniki_plus_X.open("C:\\Users\\bartek\\CLionProjects\\MO_lab2\\wyniki_plus_X");
    while(!fileX.eof()){
        fileX >> x;
        fileFun >> wynikFile;
        fileLog >> logFile;
        if(logFile > 0){
            wynik = funkcja(x);
            wynikLog = log10(abs((wynik - wynikFile) / wynikFile));
            wyniki << logFile << " " << wynikLog << "\n";
            wyniki_plus_X << x << " " << logFile << " " << wynikLog << "\n";
        } else {
            wynik = funkcjaUlepszona(x);
            wynikLog = log10(abs((wynik - wynikFile) / wynikFile));
            wyniki << logFile << " " << wynikLog << "\n";
            wyniki_plus_X << x << " " << logFile << " " << wynikLog << "\n";
        }
    }
    return 0;
}
