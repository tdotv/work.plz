#include <iostream>
#include <iomanip>
#include <math.h>

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
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //выкидываем все, что ввёл пользователь
			cout << "Oops, that input is invalid. Please try again.\n";
		}
	}
	return k;
}

int main()
{
	int** a, n, m, i, j, string, i_max, j_max, x;
	cout << "Enter size of array:" << endl;
	n = Correct_Input();
	m = Correct_Input();

	if (n <= 0 || m <= 0)
	{
		cout << "Your array can't be created" << endl;
	}

	a = new int* [n];

	for (i = 0; i < n; i++)
		a[i] = new int[m]; //формирование массива m*n

	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
		{
			cout << " a[ " << i + 1 << " ] [ " << j + 1 << " ] =  ";
			a[i][j] = Correct_Input();
		}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}

	i_max = j_max = 0;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j) {
			if (abs(a[i][j]) > abs(a[i_max][j_max]))
			{
				i_max = i;
				j_max = j;
			}
		}
	cout << " Max = " << a[i_max][j_max] << " Row = " << i_max + 1 << " Col = " << j_max + 1 << endl;

	for (int i = i_max; i < n - 1; i++) //идем до предпоследней строки, чтобы i+1 сущ
		for (int j = 0; j < m; j++)
		{
			a[i][j] = a[i + 1][j]; //приравниваем значение след строки и потом n-- удаляем
		}
	n--;

	//аналогично
	for (int i = 0; i < n; i++)
		for (int j = j_max; j < m - 1; j++)
		{
			a[i][j] = a[i][j + 1];
		}
	m--;

	//вывод
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}

	delete[]a;
}
