#include <iostream>
using namespace std;

double Drob(int, double);
double Drob_R(int);
double Correct_Input();

void main()
{
	int n, kod;
	double f = 1;
	while (true)
	{ // Ѕесконечный цикл с выходом по default
		cout << "\n\tInput n ";
		n = Correct_Input();
		cout << "\n Recurs Ц 0\n Simple Ц 1\n Else Ц Exit" << endl;
		kod = Correct_Input();
		switch (kod)
		{
		case 0:
			cout << "\t Recurs = " << Drob_R(n) << endl;
			break;
		case 1:
			cout << "\t Simple = " << Drob(n, f) << endl;
			break;
		default: return;
		}
	}
}

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
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //выкидываем все, что ввЄл пользователь
			cout << "Oops, that input is invalid. Please try again.\n";
		}
	}
	return k;
}

double Drob(int n, double f)
{
	for (int i = 1; i <= n; i++)
		f = 1 / (1 + f);
	return f;
}

double Drob_R(int n)
{
	if (n < 2) return 1;
	else
		return n * Drob_R(n - 1);
}