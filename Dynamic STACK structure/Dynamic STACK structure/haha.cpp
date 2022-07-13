#include <iostream>
#include <conio.h>
#include <iomanip>
#include <ctime>
using namespace std;

struct Stack
{
	int info;	// информационная часть
	Stack* next;	// адресная часть
};

Stack* Creat(Stack*, int);
Stack* Individual(Stack*);
Stack* Out(Stack*, int*);
int menu();
void SortMenu(Stack* start);
void Sort2(Stack* begin);
void View(Stack* begin);
void Sort1(Stack*& begin);
void Delete(Stack*& begin);

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
	Stack* start = NULL;	// указатель вершины стека
	int a, b, el;
	int kolvo = 0;

	while (true)
	{
		switch (menu())
		{
		case 1:
			if (start != NULL)
			{
				cout << "Clear Memory!\n\n";
				break;
			}
		case 2:
			do
			{
				cout << "Enter kolvo: ";
				kolvo = Correct_Input();
			} while (kolvo <= 0);

			//  Реализация рандома и ввода с клавиатуры через _getch
			cout << "Random(space) or Console(else)" << endl;
			switch (_getch())
			{
			case 32:
				cout << "Enter a and b: " << endl;
				a = Correct_Input();
				b = Correct_Input();
				srand(time(NULL));
				for (int i = 0; i < kolvo; i++)
				{
					el = rand() % (b - a + 1) + a;
					start = Creat(start, el);
				}
				break;
			default:
				cout << "Enter elements: " << endl;
				for (int i = 0; i < kolvo; i++)
				{
					el = Correct_Input();
					start = Creat(start, el);
				}
			}
			break;
			//  ----------------------------------
		case 3:
			if (!start)
			{
				cout << "Stack is empty!\n\n";
				continue;
			}
			else View(start);
			break;

		case 4:
			if (!start)
			{
				cout << "Empty\n\n";
				break;
			}
			Delete(start);
			break;

		case 5:
			if (!start)
			{
				cout << "Empty\n\n";
				break;
			}
			SortMenu(start);
			View(start);
			break;

		case 6:
			if (!start)
			{
				cout << "Empty\n\n";
				break;
			}
			start = Individual(start);
			cout << "-----Individual-----" << endl;
			View(start);
			break;

		case 7:
			exit(0);
		default:
			cout << "Please choose ur option!" << endl;
		}
	}
	system("pause");
	return 0;
}

int menu()
{
	cout << "-----Welcome to menu-----" << endl;
	cout << "1 - Creat" << endl;
	cout << "2 - Add" << endl;
	cout << "3 - View" << endl;
	cout << "4 - Delete" << endl;
	cout << "5 - Sort" << endl;
	cout << "6 - Individual" << endl;
	cout << "7 - EXIT" << endl;
	int value;
	cout << "Enter ur option: ";
	value = Correct_Input();
	system ("cls");
	return value;
}

Stack* Creat(Stack* begin, int el)
{
	Stack* St = new Stack;
	St->info = el;	// формирование информационной части
	St->next = begin;	// формирование адресной части begin = NULL
	return St;
}

void View(Stack* St)
{
	cout << "-----Stack-----" << endl;
	while (St != 0)
	{
		cout << St->info << endl;
		St = St->next;
	}
}

void Delete(Stack*& begin)	// освобождение памяти, занятой стеком
{
	Stack* St;
	while (begin != 0)
	{
		St = begin;
		begin = begin->next;
		delete St;
	}
}

void SortMenu(Stack* start)
{
	cout << "Sort1 (Space) or Sort2 (Else)" << endl;
	switch (_getch())
	{
	case 32:
		cout << "Sort1" << endl;
		Sort1(start);
		break;
	default:
		cout << "Sort2" << endl;
		Sort2(start);
		break;
	}
}

Stack* Individual(Stack* begin)
{
	Stack* St = begin;
	Stack* t;
	t = St->next;
	while (t != NULL) {
		if (t->info % 2 != 0) {
			St->next = t->next;
			delete t;
			t = St->next;
		}
		else
		{
			St = t;
			t = t->next;
		}
	}
	if (begin->info % 2 != 0) {
		t = begin;
		begin = begin->next;
		delete t;
	}
	return begin;
}

Stack* Out(Stack* begin, int* out)
{
	Stack* t = begin;
	*out = begin->info;
	begin = begin->next;
	delete t;
	return begin;
}

//перестановка адресов двух соседних элементов, следующих за элементом с известным указателем
void Sort1(Stack*& begin)
{
	begin = Creat(begin, 21);
	Stack* St = NULL, * St1, * r;
	if (begin->next->next == NULL)
		return;
	do
	{
		for (St1 = begin; St1->next->next != St; St1 = St1->next)
			if (St1->next->info > St1->next->next->info)
			{
				r = St1->next->next;
				St1->next->next = r->next;
				r->next = St1->next;
				St1->next = r;
			}
		St = St1->next;
	} while (begin->next->next != St);
	St = begin;
	begin = begin->next;
	delete St;
}

//обмен информацией между текущим и следующим элементами
void Sort2(Stack* begin)
{
	Stack* St = NULL, * St1;
	int r;
	do
	{
		for (St1 = begin; St1->next != St; St1 = St1->next)
			if (St1->info > St1->next->info)
			{
				r = St1->info;
				St1->info = St1->next->info;
				St1->next->info = r;
			}
		St = St1;
	} while (begin->next != St);
}
