
// Complex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Complex
{
public:
	Complex(double r = 0.0, double i = 0.0);

	friend Complex operator+ (const Complex a, const Complex b);
	friend Complex operator- (const Complex a, const Complex b);
	friend Complex operator* (const Complex a, const Complex b);
	friend Complex operator/ (const Complex a, const Complex b);
	void print();
	void read();

private:
	double re;
	double im;
};

Complex::Complex(double r, double i)
{
	re = r;
	im = i;
}

Complex operator+ (const Complex a, const Complex b)
{
	Complex result;

	result.re = a.re + b.re;
	result.im = a.im + b.im;

	return result;
}

Complex operator- (const Complex a, const Complex b)
{
	Complex result;

	result.re = a.re - b.re;
	result.im = a.im - b.im;

	return result;
}

Complex operator* (const Complex a, const Complex b)
{
	Complex result;

	result.re = (a.re * b.re - a.im * b.im); // ac-bd
	result.im = (a.re * b.im + a.im * b.re); // ad+bc

	return result;
}

Complex operator/ (const Complex a, const Complex b)
{
	Complex result;

	result.re = (a.re * b.re + a.im * b.im) / (b.re * b.re + b.im * b.im); // (ac+bd)/(c2+d2)
	result.im = (a.im * b.re - a.re * b.im) / (b.re * b.re + b.im * b.im); // (bc-ad)/(c2+d2)

	return result;
}

void Complex::print()
{
	bool printedre = false;

	if (re != 0 || (re == 0 && im == 0))
	{
		cout << re;
		printedre = true;
	}

	if (im > 0)
	{
		if (printedre) cout << "+";
		if (im != 1) cout << im;
		cout << "i";
	}
	else if (im < 0)
	{
		if (im == -1) cout << "-";
		else cout << im;
		cout << "i";
	}
}

void Complex::read()
{
	//fix 12-i and 12+i cases
	//Complex result;

	int zeros = 0;
	string data;

	cout << "Enter your complex number: ";
	getline(cin, data);

	int len = data.length();
	if (len == 0)
	{
		re = 0;
		im = 0;
		return;
	}//return Complex(0, 0);

	if (len == 1 || len == 2)
	{
		if (data[0] == '-' && data[1] == 'i' && len == 2)
		{
			re = 0;
			im = -1;
			return;
		}
		if (data[0] == 'i' && len == 1)
		{
			re = 0;
			im = 1;
			return;
		}
	}

	double real = stod(data);
	string reals = to_string(real);
	int lenr = reals.length();

	for (int i = lenr - 1; i >= 0; i--)
	{
		if (zeros == 6) //because 6 numbers after comma
		{
			lenr = lenr - 1;
			break;
		}
		if (reals[i] != '0') break;
		else
		{
			lenr = lenr - 1;
			zeros++;
		}
	}
	double imag;
	if (len == lenr) imag = 0;
	else if (len == lenr + 1)
	{
		real = 0;
		imag = stod(data);
	}
	else if (len == lenr + 2)
	{
		if (data[lenr] == '-') imag = -1;
		else if (data[lenr] == '+') imag = 1;
		else imag = 0;
	}
	else imag = stod(data.substr(lenr, len - lenr));

	//cout << " re: " << stod(data) << " im: " << stod(data.substr(lenr, len - lenr));
	//cout << " len = " << len << " reals = " << reals << " lenr = " << lenr << " rest: " << data.substr(lenr,len-lenr);

	//result = Complex(real, imag);
	//return result;
	re = real;
	im = imag;
}

int main()
{
	Complex a, b;
	Complex sum, difference, product, quotient;

	a.read();
	b.read();

	//cout << endl << endl << " a = " << a << endl << " b = " << b << endl << endl;
	cout << endl << endl << " a = ";
	a.print();
	cout << endl << " b = ";
	b.print();
	cout << endl << endl;

	sum = a+b;
	difference = a-b;
	product = a*b;
	quotient = a/b;

	cout << "a + b = ";
	sum.print();
	cout << endl;
	cout << "a - b = ";
	difference.print();
	cout << endl;
	cout << "a * b = ";
	product.print();
	cout << endl;
	cout << "a / b = ";
	quotient.print();
	cout << endl;


	getchar();
	return 0;
}