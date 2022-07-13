#include <ctime>
#include <iostream>
#include <iomanip>
#include <cstdlib>
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
			cout << "Oops, that input is invalid. Please try again.\n";
		}
	}
	return k;
}

void generateArray(int* a, int n);
void showArray(int* a, int n);
void sortArray(int* a, int n);
void deleteEvenNumbers(int* a, int& n);

int main()
{
	srand(time(0));
	int n;
	cout << "Enter size of array=";
	n = Correct_Input();

	while (n < 1 || n>20)
	{
		cout << "Enter correct size";
		n = Correct_Input();
	}
	int* a = new int[n];

	generateArray(a, n);
	cout << endl;

	sortArray(a, n);
	showArray(a, n);

	cout << "\nAfter deleting even numbers:" << endl;
	deleteEvenNumbers(a, n);

	showArray(a, n);
	sortArray(a, n);

	delete[]a;
	return 0;
}

void generateArray(int* a, int n)
{
	int check, i;

	cout << "Choose your way of filling the array. 1 - random, 2 - manually" << endl;
	check = Correct_Input();
	if (check == 1)
	{
		cout << "Your random array:" << endl;
		for (i = 0; i < n; i++)
		{
			a[i] = rand() % 101 - 50; //rand() % (max_number + 1 - minimum_number) + minimum_number
			cout << setw(5) << a[i];
		}
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			cout << "a[" << i + 1 << "]=";
			cin >> a[i];
		}
	}
}
void showArray(int* a, int n)
{
	int i;
	for (i = 0; i < n; i++)
		cout << setw(5) << a[i] << " ";
}

void sortArray(int* a, int n)
{
	int i, j;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[i])
			{
				swap(a[j], a[i]);
			}
		}
	}
}

void deleteEvenNumbers(int* a, int& n)
{
	int i, j;
	for (int i = 0; i < n; i++)
	{
		if (a[i] % 2 == 0)
		{
			for (int j = i; j < n - 1; j++)
			{
				a[j] = a[j + 1];
			}
			n--;
			i--;
		}
	}
}
