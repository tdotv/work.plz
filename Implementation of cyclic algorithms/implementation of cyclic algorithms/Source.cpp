#include <iostream>
#include <math.h>
#include <iomanip>

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
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Oops, that input is invalid.  Please try again.\n" << endl;
		}
	}
	return k;
}


int main()
{
	setlocale(LC_ALL, "rus");
	double b, h, x, a, r;
	double resultS = 0, resultY = 0, resultF = 0;
	int k, n;

	cout << "¬ведите a: ";
	a = Correct_Input(); //0.1
	cout << "¬ведите b: ";
	b = Correct_Input(); //1
	cout << "¬ведите h: ";
	h = Correct_Input(); //0.1
	cout << "¬ведите n: ";
	n = Correct_Input();

	cout << setw(20) << "x" << setw(20) << "Y(x)" << setw(20) << "S(x)" << setw(20) << "|Y(x) - S(x)|" << endl;

	for (x = a; x <= b; x += h)
	{
		resultY = -log(sqrt(1 + x * x)) + x * atan(x);
		resultS = 0;
		r = -1;
		for (k = 1; k <= n; k++)
		{
			r *= -x * x;
			resultS += r / (2. * k * (2. * k - 1.));
		}
		resultF = fabs(resultY - resultS);
		cout << setw(20) << x << setw(20) << resultY << setw(20) << resultS << setw(20) << resultF << endl;
	}
	return 0;
}
