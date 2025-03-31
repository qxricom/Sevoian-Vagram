#include <iostream>
#include "polynomial.h"
#include <ctime>
using namespace std;

int main() {
	srand(time(0));

	// Generation of Polynomials
	double K1[4] = { 0, 0, 0, 0 };
	for (int j = 0; j < 4; j++) {
		K1[j] = rand() % 21 - 10;
	}
	Polynomial P1(3, K1);
	VectPolynomial V1(P1);
	for (int i = 0; i < 3; i++) {
		double iK[4] = { 0, 0, 0, 0 };
		for (int j = 0; j < 4; j++) {
			iK[j] = rand() % 21 - 10;
		}
		Polynomial ip(3, iK);
		V1.Add_polynomial(ip);
	}
	V1.Print();
	cout << endl;

	double K2[4] = { 0, 0, 0, 0 };
	for (int j = 0; j < 4; j++) {
		K2[j] = rand() % 21 - 10;
	}
	Polynomial P2(3, K2);
	VectPolynomial V2(P2);
	for (int i = 0; i < 3; i++) {
		double iK[4] = { 0, 0, 0, 0 };
		for (int j = 0; j < 4; j++) {
			iK[j] = rand() % 21 - 10;
		}
		Polynomial ip(3, iK);
		V2.Add_polynomial(ip);
	}
	V2.Print();
	cout << endl;

	// Operations with odd and even Polynomials
	Polynomial sumP = addition(V1.Polynomial_at(0), V2.Polynomial_at(1));
	VectPolynomial V3(sumP);
	for (int i = 1; i < 4; i++) {
		if (i % 2 == 0) {
			Polynomial Pi = addition(V1.Polynomial_at(i), V2.Polynomial_at(i + 1));
			V3.Add_polynomial(Pi);
		}
		else {
			Polynomial Pi = addition(V1.Polynomial_at(i), V2.Polynomial_at(i - 1));
			V3.Add_polynomial(Pi);
		}
	}
	V3.Print();
	cout << endl;

	Polynomial subP = substraction(V1.Polynomial_at(0), V2.Polynomial_at(1));
	VectPolynomial V4(subP);
	for (int i = 1; i < 4; i++) {
		if (i % 2 == 0) {
			Polynomial Pi = substraction(V1.Polynomial_at(i), V2.Polynomial_at(i + 1));
			V4.Add_polynomial(Pi);
		}
		else {
			Polynomial Pi = substraction(V1.Polynomial_at(i), V2.Polynomial_at(i - 1));
			V4.Add_polynomial(Pi);
		}
	}
	V4.Print();
	cout << endl;

	return 0;
}