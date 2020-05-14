#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include "Complex.h"
using namespace std;

class Polynomial {
public:
    Polynomial();
    ~Polynomial();
    Polynomial(double *A, int len);
    Polynomial(const Polynomial &P);
    vector<double> a;
    int size() const;
    friend ostream &operator << (ostream &out, const Polynomial &P);
    Polynomial operator + (const Polynomial &P);
    Polynomial operator - (const Polynomial &P);
    Polynomial operator * (const Polynomial &P);
private:
    void FFT(Complex *A, int len, int f);
};

#endif