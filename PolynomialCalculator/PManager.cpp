#include "PManager.h"

PManager::PManager() {
    mapPoly.clear();
}

PManager::~PManager() {
    mapPoly.clear();
}

void PManager::addPolynomial(string name, Polynomial p) {
    mapPoly[name] = p;
}

Polynomial PManager::getPolynomial(string name) {
    return mapPoly[name];
}

void PManager::calculate(string str) {

}