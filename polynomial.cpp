#include "polynomial.h"
#include <cmath>


Polynomial::Polynomial(int degree, double* coefficients) {
	for (int i = 0; i < degree + 1; i++) {
		this->exponents.push_back(i);
		this->coefficients.push_back(*(coefficients + i));
	}
}
Polynomial::Polynomial(int degree) {
	for (int i = 0; i < degree + 1; i++) {
		this->exponents.push_back(i);
		this->coefficients.push_back(0);
	}
}
Polynomial::Polynomial(const Polynomial& p) {
	for (int i = 0; i < p.exponents.size(); i++) {
		this->exponents.push_back(i);
		this->coefficients.push_back(p.coefficients.at(i));
	}
}
Polynomial::~Polynomial() {

}

double Polynomial::get_coefficient(int index) const {
	if (index >= get_degree() || index < 0)
		return 0;
	return coefficients.at(index);
}
void Polynomial::set_coefficient(int index, double new_coefficients) {
	if (index < 0)
		return;

	while (index >= get_degree()) {
		exponents.push_back(get_degree());
		coefficients.push_back(0);
	}

	coefficients.at(index) = new_coefficients;
}
void Polynomial::reset(int degree, double* coefficients) {
	this->exponents.clear();
	this->coefficients.clear();

	for (int i = 0; i < degree + 1; i++) {
		this->exponents.push_back(i);
		this->coefficients.push_back(*(coefficients + i));
	}
}
void Polynomial::print() {
	int n = exponents.size();
	bool is_first_A_printed = false;

	for (int i = 0; i < n; i++) {
		double Ai = coefficients.at(i);

		if (Ai == 0)
			continue;

		if (is_first_A_printed) {
			if (Ai > 0) {
				cout << " + ";
			}
			if (Ai < 0) {
				cout << " - ";
				Ai *= -1;
			}
		}

		if (Ai != 1 || i == 0) {
			cout << Ai;
		}


		is_first_A_printed = true;

		if (i != 0)
			cout << "x";
		if (i > 1)
			cout << "^" << exponents.at(i);
	}
	cout << endl;
}
double Polynomial::calculate(double x) {
	double output = get_coefficient(0);
	int n = get_degree() + 1;
	for (int i = 1; i < n; i++) {
		output += get_coefficient(i) * pow(x, i);
	}
	return output;
}

Polynomial addition (const Polynomial& p1, const Polynomial& p2) {
	int maxE = p1.get_degree() >= p2.get_degree() ? p2.get_degree() : p1.get_degree();
	Polynomial output(maxE);

	for (int i = 0; i < maxE + 1; i++) {
		output.set_coefficient(i, p1.get_coefficient(i) + p2.get_coefficient(i));
	}
	return output;
}
Polynomial substraction (const Polynomial& p1, const Polynomial& p2) {
	int maxE = p1.get_degree() >= p2.get_degree() ? p1.get_degree() : p2.get_degree();
	Polynomial output(maxE);

	for (int i = 0; i < maxE + 1; i++) {
		output.set_coefficient(i, p1.get_coefficient(i) - p2.get_coefficient(i));
	}
	return output;
}

VectPolynomial::VectPolynomial(Polynomial& p) {
	polynoms.push_back(p);
}
VectPolynomial::VectPolynomial(const VectPolynomial& vp) {
	for (int i = 0; i < polynoms.size(); i++) {
		polynoms.push_back(vp.polynoms.at(i));
	}
}
VectPolynomial::~VectPolynomial() {

}

Polynomial& VectPolynomial::Polynomial_at(int index) {
	if (index > Get_number_of_polynomials() - 1) {
		Polynomial PolynomialZero(0);
		return PolynomialZero;
	}
	return polynoms.at(index);
}
void VectPolynomial::Remove_polynomial_at(int index) {
	if (index < 0 || index > Get_number_of_polynomials() - 1)
		return;
	polynoms.erase(polynoms.begin() + index);
}

void VectPolynomial::Print() {
	for (int i = 0; i < Get_number_of_polynomials(); i++) {
		polynoms.at(i).print();
	}
}
