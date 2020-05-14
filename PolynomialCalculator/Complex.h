#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
public:
    Complex(double a, double b);
    Complex operator + (const Complex &A) const;
    Complex operator - (const Complex &A) const;
    Complex operator - (void);
    Complex operator * (const Complex &A) const;
private:
    double a, b;
};

#endif