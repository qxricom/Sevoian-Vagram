#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Polynomial {
private:
	vector<double> coefficients;
	vector<int> exponents;

public:
	Polynomial(int degree, double* A);
	Polynomial(int degree);
	Polynomial(const Polynomial& p);
	~Polynomial();

	double get_degree() const { return exponents.size(); };
	double get_coefficient(int index) const;
	void set_coefficient(int index, double new_coefficients);
	void reset(int degree, double* coefficients);
	void print();
	double calculate(double x);
};
Polynomial addition (const Polynomial& p1, const Polynomial& p2);
Polynomial substraction (const Polynomial& p1, const Polynomial& p2);

class VectPolynomial {
private:
	vector<Polynomial> polynoms;

public:
	VectPolynomial(Polynomial& p);
	VectPolynomial(const VectPolynomial& vp);
	~VectPolynomial();

	int Get_number_of_polynomials() { return polynoms.size(); };

	Polynomial& Polynomial_at(int index);
	void Add_polynomial(Polynomial& p) { polynoms.push_back(p); };
	void Remove_polynomial_at(int index);

	void Print();
};
