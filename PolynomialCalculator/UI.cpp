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
    cout << "========== Polynomial Calculator ==========" << endl;
    cout << "Please input an order:" << endl;
    cout << "1: Add a polynomial" << endl;
    cout << "2: Calculate" << endl;
    cout << "3: Exit" << endl;
    cout << "===========================================" << endl;
    int opt, exec = 0;
    while (1) {
        cin >> opt;
        switch (opt) {
        case 1:
            addPolynomial();
            break;
        case 2:
            calculate();
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
    cout << "Please input the length of the polynomial: ";
    int len;
    cin >> len;
    cout << "Please input the coefficients:" << endl;
    double *A = new double[len];
    for (int i = 0; i < len; ++i) cin >> A[i];
    Polynomial p = Polynomial(A, len);
    string name;
    cout << "Please input the name of the polynomial: ";
    cin >> name;
    for (int i = 0; i < name.size(); ++i) {
        if (!isalpha(name[i])) {
            cout << "The name of the polynomial only consists of letters!" << endl;
            return;
        }
    }
    manager->addPolynomial(name, p);
    cout << name << " = " << p << endl;
}

void UI::calculate() {
    cout << "Please input the expression: " << endl;
    string str;
    getline(cin, str);
    getline(cin, str);
    if (manager->calculate(str)) cout << "The expression is illegal!" << endl;
}