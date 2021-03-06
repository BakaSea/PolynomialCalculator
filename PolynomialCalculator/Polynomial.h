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
    Polynomial(double a0);
    Polynomial(double *A, int len);
    Polynomial(const Polynomial &P);
    vector<double> a;
    int size() const;
    void normalize();
    double value(double x);
    Polynomial reverse() const;
    Polynomial mod(int n) const;
    Polynomial fill(int n) const;
    friend ostream &operator << (ostream &out, const Polynomial &P);
    Polynomial operator + (const Polynomial &P);
    Polynomial operator - (const Polynomial &P);
    Polynomial operator - (void);
    Polynomial operator * (const Polynomial &P);
    Polynomial operator / (const Polynomial &P);
    Polynomial operator % (const Polynomial &P);
    Polynomial inv(int n);
    Polynomial derivate();
    Polynomial integrate();
    Polynomial integrate(double a, double b);
    double root();
private:
    void FFT(Complex *A, int len, int f);
};

#endif