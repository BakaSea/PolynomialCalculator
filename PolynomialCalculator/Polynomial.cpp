#include "Polynomial.h"
#define EPS 1e-10
#define PI acos(-1.0)

Polynomial::Polynomial() {
    a.clear();
}

Polynomial::~Polynomial() {
    a.clear();
}

Polynomial::Polynomial(double a0) {
    a.clear();
    a.push_back(a0);
    normalize();
}

Polynomial::Polynomial(double *A, int len) {
    a.clear();
    for (int i = len-1; i >= 0; --i) a.push_back(A[i]);
    normalize();
}

Polynomial::Polynomial(const Polynomial &P) {
    a.clear();
    for (int i = 0; i < P.size(); ++i) {
        a.push_back(P.a[i]);
    }
    normalize();
}

int Polynomial::size() const {
    return a.size();
}

void Polynomial::normalize() {
    while (a.size() > 1 && fabs(a.back()) < EPS) a.pop_back();
}

double Polynomial::value(double x) {
    double f = 0;
    for (int i = size()-1; i >= 0; --i) {
        f = f*x+a[i];
    }
    return f;
}

Polynomial Polynomial::reverse() const {
    int n = a.size();
    double *A = new double[n];
    for (int i = 0; i < n; ++i) A[i] = a[i];
    return Polynomial(A, n);
}

Polynomial Polynomial::mod(int n) const {
    double *A = new double[n];
    for (int i = 0; i < n; ++i) A[n-i-1] = a[i];
    return Polynomial(A, n);
}

Polynomial Polynomial::fill(int n) const {
    Polynomial P(*this);
    while (P.size() < n) P.a.push_back(0);
    return P;
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

Polynomial Polynomial::operator - (void) {
    return Polynomial(0)-(*this);
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

Polynomial Polynomial::operator / (const Polynomial &P) {
    Polynomial F = reverse(), G = P.reverse();
    int n = size(), m = P.size();
    Polynomial Ginv = G.inv(n-m+1);
    return (F*Ginv).mod(n-m+1).fill(n-m+1).reverse();
}

Polynomial Polynomial::operator % (const Polynomial &P) {
    return (*this)-(*this/P)*P;
}

Polynomial Polynomial::inv(int n) {
    if (n == 1) return Polynomial(1.0/a[0]);
    Polynomial f0 = inv(ceil(1.0*n/2.0));
    Polynomial finv = f0*(Polynomial(2)-(*this)*f0);
    return finv.mod(n);
}

Polynomial Polynomial::derivate() {
    int n = size();
    if (n == 1) return Polynomial(0);
    double *A = new double[n-1];
    for (int i = n-1; i; --i) {
        A[n-i-1] = a[i]*i;
    }
    return Polynomial(A, n-1);
}

Polynomial Polynomial::integrate() {
    int n = size();
    double *A = new double[n+1];
    A[n] = 0;
    for (int i = n-1; i >= 0; --i) {
        A[n-i-1] = a[i]/(i+1);
    }
    return Polynomial(A, n+1);
}

Polynomial Polynomial::integrate(double a, double b) {
    Polynomial F = integrate();
    return Polynomial(F.value(b)-F.value(a));
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

double Polynomial::root() {
    double x = 6, y = 0;
    Polynomial F = derivate();
    double fx = value(x), ffx = F.value(x);
    if (fabs(value(x)) < EPS) return x;
    while (fabs(x-y) >= EPS) {
        x = y;
        fx = value(x);
        ffx = F.value(x);
        y = x-fx/ffx;
        if (fabs(value(y)) < EPS) break;
    }
    return y;
}