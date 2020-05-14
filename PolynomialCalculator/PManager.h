#ifndef PMANAGER_H
#define PMANAGER_H
#include <unordered_map>
#include <stack>
#include "Polynomial.h"
using namespace std;

class PManager {
public:
    PManager();
    ~PManager();
    void addPolynomial(string name, Polynomial p);
    Polynomial getPolynomial(string name);
    void calculate(string str);
private:
    unordered_map<string, Polynomial> mapPoly;
    stack<string> stkOpt;
    stack<Polynomial> stkPoly;
};

#endif