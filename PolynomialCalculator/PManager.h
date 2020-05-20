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
    int calculate(string str);
    void getRoot(string name);
    void getInverse(string name);
private:
    struct MyOperator {
        char opt;
        Polynomial a, b;
        int pos;
        MyOperator() {}
        MyOperator(char opt, int pos): opt(opt), pos(pos) {}
        MyOperator(char opt, Polynomial a, Polynomial b, int pos) : opt(opt), a(a), b(b), pos(pos) {}
    };
    struct MyPolynomial {
        Polynomial P;
        int depth, pos;
        MyPolynomial() {}
        MyPolynomial(Polynomial P, int depth, int pos) : P(P), depth(depth), pos(pos) {}
    };
    unordered_map<string, Polynomial> mapPoly;
    stack<MyOperator> stkOpt;
    stack<MyPolynomial> stkPoly;
    int depth;
    int analyze(string str, int &p, int size);
    int getPriority(char opt);
    int calStack();
};

#endif