#include "Polynomial.h"
#define EPS 1e-6
#define PI acos(-1.0)

Polynomial::Polynomial() {
    a.clear();
}

Polynomial::~Polynomial() {
    a.clear();
}

Polynomial::Polynomial(double *A, int len) {
    a.clear();
    for (int i = len-1; i >= 0; --i) a.push_back(A[i]);
    while (a.size() > 1 && fabs(a.back()) < EPS) a.pop_back();
}

Polynomial::Polynomial(const Polynomial &P) {
    a.clear();
    for (int i = 0; i < P.size(); ++i) {
        a.push_back(P.a[i]);
    }
}

int Polynomial::size() const {
    return a.size();
}

ostream &operator << (ostream &out, const Polynomial &P) {
    int flag = 0;
    for (int i = P.a.size()-1; i >= 0; --i) {
        if (fabs(P.a[i]) < EPS) continue;
        if (P.a[i] > 0 && flag) out << '+';
        if (P.a[i] < 0) out << '-';
        if (!i || (fabs(P.a[i]-1) > EPS) && fabs(P.a[i]+1) > EPS) out << fabs(P.a[i]);
        if (i) {
            out << 'x';
            if (i != 1) out << '^' << i;
        }
        flag = 1;
    }
    if (!flag) out << '0';
    return out;
}

Polynomial Polynomial::operator + (const Polynomial &P) {
    Polynomial C = Polynomial();
    int n = min(this->size(), P.size());
    for (int i = 0; i < n; ++i) {
        C.a.push_back(a[i]+P.a[i]);
    }
    if (this->size() > n) {
        for (int i = n; i < this->size(); ++i) {
            C.a.push_back(a[i]);
        }
    } else for (int i = n; i < P.size(); ++i) {
        C.a.push_back(P.a[i]);
    }
    return C;
}

Polynomial Polynomial::operator - (const Polynomial &P) {
    Polynomial C = Polynomial();
    int n = min(this->size(), P.size());
    for (int i = 0; i < n; ++i) {
        C.a.push_back(a[i]-P.a[i]);
    }
    if (this->size() > n) {
        for (int i = n; i < this->size(); ++i) {
            C.a.push_back(a[i]);
        }
    } else for (int i = n; i < P.size(); ++i) {
        C.a.push_back(-P.a[i]);
    }
    return C;
}

Polynomial Polynomial::operator * (const Polynomial &P) {
    int n = size(), m = P.size(), nm = 1;
    while (nm < n*2 || nm < m*2) nm <<= 1;
    Complex *A = new Complex[nm], *B = new Complex[nm];
    for (int i = 0; i < n; ++i) A[i] = Complex(a[i], 0);
    for (int i = n; i < nm; ++i) A[i] = Complex(0, 0);
    for (int i = 0; i < m; ++i) B[i] = Complex(P.a[i], 0);
    for (int i = m; i < nm; ++i) B[i] = Complex(0, 0);
    FFT(A, nm, 1); FFT(B, nm, 1);
    for (int i = 0; i < nm; ++i) A[i] = A[i]*B[i];
    FFT(A, nm, -1);
    double *C = new double[nm];
    for (int i = 0; i < nm; ++i) C[i] = A[nm-i-1].a;
    return Polynomial(C, nm);
}

void Polynomial::FFT(Complex *A, int len, int f) {
    for (int i = 1, j = len >> 1; i < len-1; ++i) {
        if (i < j) swap(A[i], A[j]);
        int k = len >> 1;
        while (j >= k) {
            j -= k;
            k >>= 1;
        }
        if (j < k) j += k;
    }
    for (int i = 2; i <= len; i <<= 1) {
        Complex wn(cos(2*PI/i), sin(f*2*PI/i));
        for (int j = 0; j < len; j += i) {
            Complex w(1, 0);
            for (int k = j; k < j+i/2; ++k) {
                Complex u = A[k], t = w*A[k+i/2];
                A[k] = u+t;
                A[k+i/2] = u-t;
                w = w*wn;
            }
        }
    }
    if (f == -1) {
        for (int i = 0; i < len; ++i) {
            A[i].a /= len;
        }
    }
}