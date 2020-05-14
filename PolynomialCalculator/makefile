main:main.o Polynomial.o Complex.o PManager.o UI.o
	g++ main.o Polynomial.o Complex.o PManager.o UI.o -o PolynomialCalculator
main.o:main.cpp
	g++ -c main.cpp
Polynomial.o:Polynomial.cpp
	g++ -c Polynomial.cpp
Complex.o:Complex.cpp
	g++ -c Complex.cpp
UI.o:UI.cpp
	g++ -c UI.cpp
PManager.o:PManager.cpp
	g++ -c PManager.cpp

clean:
	rm *.o
	rm PolynomialCalculator