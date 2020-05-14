#include "Complex.h"

Complex::Complex() {
    a = b = 0;
}

Complex::Complex(double a, double b) : a(a), b(b) {

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