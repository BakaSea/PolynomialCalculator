#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <string>
#include <vector>
#include "Complex.h"
using namespace std;

class Polynomial {
public:
    Polynomial();
    vector<double> a;
    int size();
    Polynomial operator + (Polynomial &A);
    Polynomial operator - (Polynomial &A);
    Polynomial operator * (Polynomial &A);
private:
    void FFT(Complex *A, int len, int f);
};

#endif