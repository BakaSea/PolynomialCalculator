#include "Polynomial.h"
#include <iostream>

Polynomial::Polynomial() {
    a.clear();
}

int Polynomial::size() {
    return a.size();
}

Polynomial Polynomial::operator + (Polynomial &A) {
    Polynomial C = Polynomial();
    int n = min(this->size(), A.size());
    for (int i = 0; i < n; ++i) {
        C.a.push_back(a[i]+A.a[i]);
    }
    if (this->size() > n) {
        for (int i = n; i < this->size(); ++i) {
            C.a.push_back(a[i]);
        }
    } else for (int i = n; i < A.size(); ++i) {
        C.a.push_back(A.a[i]);
    }
    return C;
}

Polynomial Polynomial::operator - (Polynomial &A) {
    Polynomial C = Polynomial();
    int n = min(this->size(), A.size());
    for (int i = 0; i < n; ++i) {
        C.a.push_back(a[i]-A.a[i]);
    }
    if (this->size() > n) {
        for (int i = n; i < this->size(); ++i) {
            C.a.push_back(a[i]);
        }
    } else for (int i = n; i < A.size(); ++i) {
        C.a.push_back(-A.a[i]);
    }
    return C;
}

Polynomial Polynomial::operator * (Polynomial &A) {
    Polynomial C = Polynomial();
    //TODO: FFT
    return C;
}

void Polynomial::FFT(Complex *A, int len, int f) {
    
}