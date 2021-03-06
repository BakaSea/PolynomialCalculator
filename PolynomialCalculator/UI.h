#ifndef UI_H
#define UI_H
#include "PManager.h"

class UI {
public:
    UI();
    ~UI();
    void show();
private:
    PManager *manager;
    void addPolynomial();
    void deletePolynomial();
    void showPolynomial();
    void calculate();
    void getRoot();
    void getInverse();
};

#endif