#include "PManager.h"
#include <math.h>

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

int PManager::calculate(string str) {
	while (!stkOpt.empty()) stkOpt.pop();
	while (!stkPoly.empty()) stkPoly.pop();
	int p = 0;
	depth = 0;
	if (analyze(str, p, 0)) return 1;
	cout << stkPoly.top().P << endl;
	return 0;
}

void PManager::getRoot(string name) {
	unordered_map<string, Polynomial>::iterator iter = mapPoly.find(name);
	if (iter == mapPoly.end()) cout << name << " does not exist!" << endl;
	else cout << "The root is " << iter->second.root() << endl;
}

void PManager::getInverse(string name) {
	unordered_map<string, Polynomial>::iterator iter = mapPoly.find(name);
	if (iter == mapPoly.end()) cout << name << " does not exist!" << endl;
	else {
		if (fabs(iter->second.a[0]) < 1e-10) cout << name << " has no inverse!" << endl;
		else cout << iter->second.inv(iter->second.size()) << endl;
	}
}

int PManager::analyze(string str, int& p, int size) {
	string F = string();
	int dot = 0, xs = 0;
	double x = 0;
	for (; p < str.size(); ++p) {
		if (isdigit(str[p])) {
			if (!xs) xs = 1;
			if (!F.empty()) {
				unordered_map<string, Polynomial>::iterator iter = mapPoly.find(F);
				if (iter != mapPoly.end()) {
					stkPoly.push(MyPolynomial(iter->second, depth, p - 1));
				} else return 1;
			}
			F.clear();
			if (!dot) x = x * 10 + str[p] - '0';
			else {
				dot *= 10;
				x += 1.0 * (str[p] - '0') / (1.0 * dot);
			}
		} else if (str[p] == '.') {
			if (!F.empty()) {
				unordered_map<string, Polynomial>::iterator iter = mapPoly.find(F);
				if (iter != mapPoly.end()) {
					stkPoly.push(MyPolynomial(iter->second, depth, p - 1));
				} else return 1;
			}
			F.clear();
			if (dot) return 1;
			dot = 1;
		} else if (isalpha(str[p])) {
			if (xs) stkPoly.push(MyPolynomial(Polynomial(x), depth, p - 1));
			x = dot = xs = 0;
			F.push_back(str[p]);
		} else {
			if (xs) stkPoly.push(MyPolynomial(Polynomial(x), depth, p - 1));
			x = dot = xs = 0;
			if (!F.empty()) {
				unordered_map<string, Polynomial>::iterator iter = mapPoly.find(F);
				if (iter != mapPoly.end()) {
					stkPoly.push(MyPolynomial(iter->second, depth, p - 1));
				} else return 1;
			}
			F.clear();
			if (str[p] == ' ' || str[p] == '\t') continue;
			if (str[p] == '(') {
				stkOpt.push(MyOperator('(', p));
				depth++;
			} else if (str[p] == ')') {
				while (stkOpt.size() > size && stkOpt.top().opt != '(') {
					if (calStack()) return 1;
					stkOpt.pop();
				}
				if (stkOpt.size() <= size) return 1;
				MyPolynomial P = stkPoly.top();
				stkPoly.pop();
				P.depth--;
				stkPoly.push(P);
				stkOpt.pop();
				depth--;
			} else if (str[p] == '$') {
				int pos = p++;
				if (p >= str.size()) return 1;
				if (str[p] == '[') {
					p++;
					if (analyze(str, p, stkPoly.size())) return 1;
					Polynomial a = stkPoly.top().P;
					stkPoly.pop();
					if (a.size() > 1) return 1;
					p++;
					if (analyze(str, p, stkPoly.size())) return 1;
					Polynomial b = stkPoly.top().P;
					stkPoly.pop();
					if (b.size() > 1) return 1;
					stkOpt.push(MyOperator('$', a, b, pos));
				} else return 1;
			} else if (str[p] == '!' || str[p] == '*' || str[p] == '/' || str[p] == '+' || str[p] == '-' || str[p] == '%') {
				if (stkOpt.size() == size) stkOpt.push(MyOperator(str[p], p));
				else {
					if (getPriority(str[p]) >= getPriority(stkOpt.top().opt)) stkOpt.push(MyOperator(str[p], p));
					else {
						while (stkOpt.size() > size && stkOpt.top().opt != '(' && getPriority(str[p]) < getPriority(stkOpt.top().opt)) {
							if (calStack()) return 1;
							stkOpt.pop();
						}
						stkOpt.push(MyOperator(str[p], p));
					}
				}
			} else if (str[p] == ']') {
				break;
			} else if (str[p] == ',') {
				break;
			}
		}
	}
	if (xs) stkPoly.push(MyPolynomial(Polynomial(x), depth, p - 1));
	if (!F.empty()) {
		unordered_map<string, Polynomial>::iterator iter = mapPoly.find(F);
		if (iter != mapPoly.end()) {
			stkPoly.push(MyPolynomial(iter->second, depth, p - 1));
		} else return 1;
	}
	while (stkOpt.size() > size) {
		if (calStack()) return 1;
		stkOpt.pop();
	}
	if (stkOpt.size() == size && stkPoly.size() == size+1) return 0;
	return 1;
}

int PManager::getPriority(char opt) {
	if (opt == '(') return 4;
	if (opt == '!') return 3;
	if (opt == '$') return 3;
	if (opt == '*') return 2;
	if (opt == '/') return 2;
	if (opt == '+') return 1;
	if (opt == '-') return 1;
	if (opt == '%') return 0;
}

int PManager::calStack() {
	if (stkPoly.empty()) return 1;
	MyPolynomial G = stkPoly.top();
	stkPoly.pop();
	MyOperator opt = stkOpt.top();
	switch (opt.opt) {
	case '(': return 1;
	case '!':
		if (depth != G.depth) return 1;
		if (G.pos >= opt.pos) return 1;
		stkPoly.push(MyPolynomial(G.P.derivate(), G.depth, G.pos));
		break;
	case '$': {
		if (G.pos <= opt.pos) return 1;
		stkPoly.push(MyPolynomial(G.P.integrate(opt.a.a[0], opt.b.a[0]), G.depth, G.pos));
		break;
	}
	case '*': {
		if (stkPoly.empty()) return 1;
		MyPolynomial F = stkPoly.top();
		stkPoly.pop();
		if (F.depth != G.depth) return 1;
		stkPoly.push(MyPolynomial(F.P * G.P, G.depth, F.pos));
		break;
	}
	case '/': {
		if (stkPoly.empty()) return 1;
		MyPolynomial F = stkPoly.top();
		stkPoly.pop();
		if (F.depth != G.depth) return 1;
		stkPoly.push(MyPolynomial(F.P / G.P, G.depth, F.pos));
		break;
	}
	case '+': {
		if (stkPoly.empty()) return 1;
		MyPolynomial F = stkPoly.top();
		stkPoly.pop();
		if (F.depth != G.depth) return 1;
		stkPoly.push(MyPolynomial(F.P + G.P, G.depth, F.pos));
		break;
	}
	case '-': {
		if (stkPoly.empty()) stkPoly.push(MyPolynomial(-G.P, G.depth, G.pos));
		else {
			MyPolynomial F = stkPoly.top();
			stkPoly.pop();
			if (F.depth != G.depth) {
				stkPoly.push(F);
				stkPoly.push(MyPolynomial(-G.P, G.depth, G.pos));
			} else stkPoly.push(MyPolynomial(F.P - G.P, G.depth, F.pos));
		}
		break;
	}
	case '%': {
		if (stkPoly.empty()) return 1;
		MyPolynomial F = stkPoly.top();
		stkPoly.pop();
		if (F.depth != G.depth) return 1;
		stkPoly.push(MyPolynomial(F.P % G.P, G.depth, F.pos));
		break;
	}
	default:
		break;
	}
	return 0;
}