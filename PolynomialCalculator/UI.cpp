#include "UI.h"
#include <iostream>
using namespace std;

UI::UI() {
    manager = new PManager();
}

UI::~UI() {
    delete manager;
}

void UI::show() {
    int opt, exec = 0;
    while (1) {
        cin >> opt;
        switch (opt) {
        case 1:
            addPolynomial();
            break;
        case 2:
            break;
        case 3:
            exec = 1;
            break;
        default:
            break;
        }
        if (exec) break;
    }
}

void UI::addPolynomial() {
    int len;
    cin >> len;
    double *A = new double[len];
    for (int i = 0; i < len; ++i) cin >> A[i];
    Polynomial p = Polynomial(A, len);
    string name;
    cin >> name;
    manager->addPolynomial(name, p);
    cout << name << " = " << p << endl;
}