#include "Complex.h"

Complex::Complex(double a = 0, double b = 0) : a(a), b(b) {

}

Complex Complex::operator + (const Complex &A) const {
    return Complex(a+A.a, b+A.b);
}

Complex Complex::operator - (const Complex &A) const {
    return Complex(a-A.a, b-A.b);
}

Complex Complex::operator - (void) {
    return Complex(-a, -b);
}

Complex Complex::operator * (const Complex &A) const {
    return Complex(a*A.a-b*A.b, a*A.b+b*A.a);
}