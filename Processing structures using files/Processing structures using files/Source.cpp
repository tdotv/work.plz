#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <Windows.h>
using namespace std;

const char file_name[] = "7_lab.txt";
const int NAMESIZE = 30;

struct student
{
	char fio[NAMESIZE];
	int group;
	int workshops, lectures, laboratory;
	double average;
} spisok;

void create();
void outputRez(FILE* txtf, student stu);
void add();
void show();
void fileOutputRes();
int menu();

int n = 0;
int main()
{
	setlocale(LC_ALL, "ru");
	while (true)
	{
		switch (menu())
		{
		default: cout << "Ошибка";
		case 1: create(); break;
		case 2: show(); break;
		case 3: add(); break;
		case 4: fileOutputRes(); break;
		case 5: return 0;
		}
		system("pause");
		system("cls");
	}
	return 0;
}

int menu()
{
	cout << "1. Создание" << endl;
	cout << "2. Просмотр" << endl;
	cout << "3. Добавление" << endl;
	cout << "4. Решение индивидуального задания" << endl;
	cout << "5. Выход" << endl;
	int e;
	cout << "Введите опцию: ";
	cin >> e;
	return e;
}

void create()
{
	FILE* f;
	fopen_s(&f, file_name, "w");
	if (f == NULL)
	{
		printf("Create error\n");
		exit(0);
	}

	printf("File %s created\n", file_name);

	fclose(f);
	system("pause");
}

void show()
{
	FILE* f;
	fopen_s(&f, file_name, "r");
	if (f == NULL)
	{
		printf("Open error\n");
		exit(0);
	}
	int n = _filelength(_fileno(f)) / sizeof(student); //получаем кол-во элементов массива
	student* arr = new student[n];
	for (int i = 0; i < n; i++)
	{
		fread((arr + i), sizeof(student), 1, f);
	}
	FILE* txtf;
	fopen_s(&txtf, "showlist.txt", "w");
	if (txtf == NULL)
	{
		printf("Open error\n");
		exit(0);
	}
	for (int i = 0; i < n; i++)
	{
		outputRez(txtf, arr[i]);
	}
	fclose(txtf);
	delete[] arr;
	fclose(f);
	system("pause");
}

void outputRez(FILE* txtf, student stu)
{
	printf("surname: %s\n Group: %d\n Marks\n workshops: %d\n lectures: %d\n laboratory: %d\n average rating: %.2f\n\n", stu.fio, stu.group, stu.workshops, stu.lectures, stu.laboratory, stu.average);
	fprintf(txtf, "%s %d %d %d %d %.2f\n", stu.fio, stu.group, stu.workshops, stu.lectures, stu.laboratory, stu.average);
}

void add()
{
	FILE* f;
	//student new_student;
	fopen_s(&f, file_name, "a");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (f == NULL)
	{
		printf("Create error\n");
		exit(0);
	}
	int i, n;
	cout << "Введите количество студентов: " << endl;
	cin >> n;

	for (i = 0; i < n; i++)
	{
		cout << "Введите фамилию студента: ";
		cin >> spisok.fio;
		cout << "Номер группы: ";
		cin >> spisok.group;
		cout << "Введите 3 оценки студента за семестр: ";
		cin >> spisok.workshops >> spisok.lectures >> spisok.laboratory;
		spisok.average = (spisok.workshops + spisok.lectures + spisok.laboratory) / 3.;
		fwrite(&spisok, sizeof(student), 1, f);
	}

	fclose(f);
}

void fileOutputRes()
{
	student* arr_of_students;
	int avgmark = 0, count = 0;
	int needAvgMark;
	cout << "Введите нужный средний балл ";
	cin >> needAvgMark;
	FILE* f;
	fopen_s(&f, file_name, "r");
	if (f == NULL)
	{
		printf("Create error\n");
		exit(0);
	}

	FILE* txtf;
	fopen_s(&txtf, "anketalist.txt", "w");

	//n = _filelength(_fileno(f)) / sizeof(student);
	arr_of_students = new student[n];
	int kolvo = _filelength(_fileno(f)) / sizeof(student);

	for (int i = 0; i < kolvo; i++) {
		fread((arr_of_students + i), sizeof(student), 1, f);
		if (needAvgMark <= arr_of_students[i].average) 
		{
			printf_s("%s\n", arr_of_students[i].fio);
			fprintf_s(txtf, "%s\n", arr_of_students[i].fio);
		}
	}
	delete[]arr_of_students;
	fclose(txtf);
	fclose(f);
}
