#include <math.h>
#include <conio.h>
#include <iostream>

using namespace std;

double fun(double);
//����� ��������
double Simps(double(*f)(double), double, double, int);

int Correct_Input_Int()
{
	int k;
	while (true)
	{
		cin >> k;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear(); //������� ���� ������
			cin.ignore((numeric_limits<streamsize>::max)(), '\n'); //���������� ���, ��� ��� ������������
			cout << "Oops, that input is invalid. Please try again.\n";
		}
	}
	return k;
}
double Correct_Input_Double()
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
			cin.clear(); //������� ���� ������
			cin.ignore((numeric_limits<streamsize>::max)(), '\n'); //���������� ���, ��� ��� ������������
			cout << "Oops, that input is invalid. Please try again.\n";
		}
	}
	return k;
}

int main()
{
	setlocale(LC_ALL, "rus");
	double a, b, eps, h, Int2;
	int n, n1;
	double Int1 = 0;
	double pogr = 0;

	cout << "������� �������� ������ �������:" << endl;
	cout << "a = ";
	a = Correct_Input_Double();
	cout << "b = ";
	b = Correct_Input_Double();

	cout << "������� ���������� ��������� n = ";
	n = Correct_Input_Int();
	cout << "������� ����������� �������� eps = ";
	eps = Correct_Input_Double();
	h = (b - a) / 100;

	cout << "�������� ����� ���������� ���������: " << endl;
	cout << "1 ��� ��������� �� n, 2 - ��� �������� eps: ";
	int key = Correct_Input_Int();
	switch (key)
	{
	case 1:
	{
		cout << "������ �� ��������� �� n = " << n << ":" << endl;
		Int1 = Simps(fun, a, b, n);
		break;
	}
	case 2:
	{
		n1 = 2;
		cout << "������ �� �������� eps:" << endl;
		Int1 = Simps(fun, a, b, n1);
		do {
			n1 *= 2;
			Int2 = Simps(fun, a, b, n1);
			pogr = fabs(Int2 - Int1);
			Int1 = Int2;
		} while (pogr > eps);
		cout << "��� n = " << n << endl;
		break;
	}
	}
	cout << "�������� ��������� = " << Int1 << endl;

	system("pause");
	return 0;
}

double Simps(double(*f)(double), double a, double b, int n) {
	double s = 0, h, x;
	h = (b - a) / n;
	x = a;
	for (int i = 1; i <= n; i++) {
		s += f(x) + 4 * f(x + h / 2) + f(x + h);
		x += h;
	}
	return s * h / 6;
}

// �� ��������� [-4, 2] �������� 20.375
double fun(double x) {
	return 0.1*x*x*x+x*x-10*sin(x);
}
