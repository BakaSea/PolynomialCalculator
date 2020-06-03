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
    cout << "2: Delete a polynomial" << endl;
    cout << "3: Show all polynomials" << endl;
    cout << "4: Calculate" << endl;
    cout << "5: Get root" << endl;
    cout << "6: Get the inverse" << endl;
    cout << "7: Exit" << endl;
    cout << "===========================================" << endl;
    int opt, exec = 0;
    while (1) {
        cout << "Please input the order: ";
        cin >> opt;
        switch (opt) {
        case 1:
            addPolynomial();
            break;
        case 2:
            deletePolynomial();
            break;
        case 3:
            showPolynomial();
            break;
        case 4:
            calculate();
            break;
        case 5:
            getRoot();
            break;
        case 6:
            getInverse();
            break;
        case 7:
            exec = 1;
            break;
        default:
            cout << "Unknown order." << endl;
            break;
        }
        if (exec) break;
    }
}

void UI::addPolynomial() {
    int flag = 0;
    cout << "Please input the length of the polynomial: ";
    int len;
    cin >> len;
    if (len <= 0) {
        cout << "Please input a positive integer!" << endl;
        flag = 1;
    }
    if (!flag) {
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
                flag = 1;
                break;
            }
        }
        if (!flag) {
            if (manager->addPolynomial(name, p)) {
                cout << name << " exists!" << endl;
                flag = 1;
            } else cout << name << " = " << p << endl;
        }
    }
    if (!flag) cout << "Add successfully." << endl;
    cout << "Do you want to continue to add? (y/n): ";
    string ans;
    cin >> ans;
    if (ans == "y") addPolynomial();
}

void UI::deletePolynomial() {
    string name;
    cout << "Please input the name of the polynomial: ";
    cin >> name;
    if (manager->deletePolynomial(name)) {
        cout << name << " does not exist!" << endl;
    } else {
        cout << "Delete successfully." << endl;
    }
}

void UI::showPolynomial() {
    manager->printPolynomial();
}

void UI::calculate() {
    cout << "Please input the expression: " << endl;
    string str;
    getline(cin, str);
    getline(cin, str);
    if (manager->calculate(str)) cout << "The expression is illegal!" << endl;
    else cout << "Calculate successfully." << endl;
    cout << "Do you want to continue to calculate? (y/n): ";
    cin >> str;
    if (str == "y") calculate();
}

void UI::getRoot() {
    cout << "Please input the name of the polynomial:" << endl;
    string name;
    cin >> name;
    manager->getRoot(name);
}

void UI::getInverse() {
    cout << "Please input the name of the polynomial:" << endl;
    string name;
    cin >> name;
    manager->getInverse(name);
}