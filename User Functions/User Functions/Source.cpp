#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

double Correct_Input()
{
	double k;
	while (true)
	{
		cin >> k;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear(); //убираем флаг ошибки
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //выкидываем все, что вввел пользователь
			cout << "Oops, that input is invalid. Please try again.\n" << endl;
		}
	}
	return k;
}

void out_rez(double(*myFunc)(double, int), double a, double b, double h, double n);
double funcY(double x, int n);
double funcS(double x, int n);
double funcF(double x, int n);

int main()
{
	double a, b, h, x;
	int n;
	char code;

	cout << "Enter a = ";
	a = Correct_Input();
	cout << "Enter b = ";
	b = Correct_Input();
	cout << "Enter h = ";
	h = Correct_Input();
	cout << "Enter n = ";
	n = Correct_Input();

	do {
		cout << "1 = Y(x), 2 = S(x), 3 = |Y(x) - S(X)|" << endl;
		int item;
		cin >> item;
		switch (item)
		{
		default:
			cout << "You can enter only 1, 2 or 3!" << endl;
			break;
		case 1: out_rez(funcY, a, b, h, n);
			break;
		case 2: out_rez(funcS, a, b, h, n);
			break;
		case 3: out_rez(funcF, a, b, h, n);
			break;
		}
		cout << "Repeat - (y, Y), Else - EXIT" << endl;
		code = _getch();
	} while ((code == 'y') || (code == 'Y'));//повторить или выход
}

void out_rez(double(*myFunc)(double, int), double a, double b, double h, double n)
{
	cout << setw(15) << "x" << setw(15) << "value" << endl;
	for (double x = a; x <= b; x += h)
		cout << setw(15) << x << setw(15) << myFunc(x, n) << endl;
}

double funcY(double x, int n)
{
	return -log(sqrt(1 + x * x)) + x * atan(x);
}

double funcS(double x, int n)
{
	double s = 0, r = -1;
	for (int k = 1; k <= n; k++)
	{
		r *= -x * x;
		s += r / (2. * k * (2. * k - 1.));
	}
	return s;
}

double funcF(double x, int n)
{
	return fabs(funcY(x, n) - funcS(x, n));
}
