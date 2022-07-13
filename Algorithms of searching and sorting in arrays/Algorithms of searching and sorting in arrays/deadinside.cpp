// �������� ������ �����, ���������� ���� ��������

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const char FILENAME[] = "lab.txt";
const int NAMESIZE = 20;
const int RESERVESIZE = 100;

struct ticket
{
	char name[NAMESIZE];
	char brand[NAMESIZE];
	int key; //data
	bool rdy;
};

int Correct_Input()
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

int menu();

void writeFileEquipment(ticket* arr_of_equipment, int number_of_equipment);

void addFileEquipment(ticket new_equipment);

void readFileEquipment(ticket* arr_of_equipment, int& number_of_equipment);

int getCountOfStucturesInFile(string file_path);

void createEquipmentInArray(ticket* arr_of_equipment, int& number_of_equipment);

void addEquipmentInArray(ticket* arr_of_equipment, int& number_of_equipment);

void showEquipmentArray(ticket* arr_of_equipment, int number_of_equipment);

void linearSearch(ticket* arr_of_equipment, int& number_of_equipment);

ticket* directSort(ticket* arr_of_equipment, int& number_of_equipment);

ticket* quickSort(ticket* arr_of_equipment, int& number_of_equipment);

void dvSearch(ticket* arr_of_equipment, int& number_of_equipment);

//ticket* tzSort(ticket* arr_of_equipment, int& number_of_equipment);

void tz(ticket* arr_of_equipment, int& number_of_equipment, int& number_of_strings);

int main()
{
	setlocale(LC_ALL, "ru");
	ticket arr_of_equipment[RESERVESIZE];
	int number_of_equipment = 0;

	while (true)
	{
		switch (menu())
		{
		case 1:
			createEquipmentInArray(arr_of_equipment, number_of_equipment);
			break;
		case 2:
			addEquipmentInArray(arr_of_equipment, number_of_equipment);
			break;
		case 3:
			showEquipmentArray(arr_of_equipment, number_of_equipment);
			break;
		case 4:
			linearSearch(arr_of_equipment, number_of_equipment);
			break;
		case 5:
			directSort(arr_of_equipment, number_of_equipment);
			break;
		case 6:
			quickSort(arr_of_equipment, number_of_equipment);
			break;
		case 7:
			dvSearch(arr_of_equipment, number_of_equipment);
			break;
		/*case 8:
			tz(arr_of_equipment, number_of_equipment);
			break;*/
		case 0:
			return 0;
		default:
			cout << "Choose ur option!" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}

int menu()
{
	cout << "1-createEquipmentInArray" << endl;
	cout << "2-addEquipmentInArray" << endl;
	cout << "3-showEquipmentArray" << endl;
	cout << "4-linearSearch" << endl;
	cout << "5-directSort" << endl;
	cout << "6-quickSort" << endl;
	cout << "7-dvSearch" << endl;
	cout << "0-exit" << endl;

	int choose;
	cout << "Option: ";
	choose = Correct_Input();

	return choose;
}

void createEquipmentInArray(ticket* arr_of_equipment, int& number_of_equipment)
{
	cout << "������� ������������ ���������: ";
	cin >> arr_of_equipment[0].name;
	cout << "������� ����� ���������: ";
	cin >> arr_of_equipment[0].brand;
	cout << "������� ����: ";
	arr_of_equipment[0].key = Correct_Input();
	cout << "������� ������ �� ���������: 0 - �� ������, 1 - ������ ";
	cin >> arr_of_equipment[0].rdy;
	writeFileEquipment(&arr_of_equipment[0], 1);
}

void addEquipmentInArray(ticket* arr_of_equipment, int& number_of_equipment)
{
	//���������� ��������, ���� �� ���������� ����� �� ������� �������
	if (number_of_equipment + 1 <= RESERVESIZE)
	{
		number_of_equipment++;
		cout << "������� ������������ ���������: ";
		cin >> arr_of_equipment[number_of_equipment - 1].name;
		cout << "������� ����� ���������: ";
		cin >> arr_of_equipment[number_of_equipment - 1].brand;
		cout << "������� ����: ";
		arr_of_equipment[number_of_equipment - 1].key = Correct_Input();
		cout << "������� ������ �� ���������: 0 - �� ������, 1 - ������ ";
		cin >> arr_of_equipment[number_of_equipment - 1].rdy;
		addFileEquipment(arr_of_equipment[number_of_equipment - 1]);
	}
	else cout << "������������ ������ ��� ���������� ������ ��������!" << endl;
}

void showEquipmentArray(ticket* arr_of_equipment, int number_of_equipment)
{
	readFileEquipment(arr_of_equipment, number_of_equipment);

	for (int i = 0; i < number_of_equipment; i++)
	{
		cout << "������������ ���������: " << arr_of_equipment[i].name << endl;
		cout << "�������� ������: " << arr_of_equipment[i].brand << endl;
		cout << "���� ������ � ������: " << arr_of_equipment[i].key << endl;
		cout << "���������� ���������: 0 - �� ������, 1 - ������ " << arr_of_equipment[i].rdy << endl << endl;
	}
}

void writeFileEquipment(ticket* arr_of_equipment, int number_of_equipment)
{
	//��������� ���� ��� ������:
	ofstream fout(FILENAME, ios::binary | ios::out);
	fout.write((char*)&arr_of_equipment[0], sizeof(ticket) * number_of_equipment);
	fout.close();
}

void addFileEquipment(ticket new_equipment)
{
	//��������� ���� ��� ��������:
	ofstream fadd(FILENAME, ios::binary | ios::app);
	fadd.write((char*)&new_equipment, sizeof(new_equipment)); //�������� ���������
	fadd.close();
}

void readFileEquipment(ticket* arr_of_equipment, int& number_of_equipment)
{
	ifstream fin(FILENAME, ios::binary | ios::in);

	if (!fin.is_open()) cout << "��������� ���� �� ����������!" << endl;
	else
	{
		// ���������� ���������� ����� � �����
		int sizeOfFileWithEquipment = getCountOfStucturesInFile(FILENAME);
		// ���� ���������� ������ ��� ����������� ������ ������� ��� ������� � ����� 

		if (sizeOfFileWithEquipment <= RESERVESIZE)
		{
			// ����� ��������� ��� �������
			number_of_equipment = sizeOfFileWithEquipment;
		}
		else
		{
			// ����� ������� ����� �������, ��������� ������� ����� � �������
			number_of_equipment = RESERVESIZE;
			cout << "There is not enough memory for read all data!" << endl;

		}
		// ������ ����� number_of_students-������� �� ����� � ��������� �� � ������� 
		fin.read((char*)&arr_of_equipment[0], sizeof(ticket) * number_of_equipment);

	}
	fin.close();
}

int getCountOfStucturesInFile(string file_path)
{
	//��������� ���� � ���������� ��������� � ����� �����
	ifstream file(FILENAME, ios::ate | ios::binary);

	/*file.tellg() ���������� �������� ����
	int, ������� ����������, ������� ���������� �������� � ������ �� ������ ����� ��
	������� ������� */
	int number_of_strings = file.tellg() / sizeof(ticket);
	file.close();
	return number_of_strings;
}

void dvSearch(ticket* arr_of_equipment, int& number_of_equipment)
{
	readFileEquipment(arr_of_equipment, number_of_equipment);
	quickSort(arr_of_equipment, number_of_equipment);

	int dataSearch;
	cout << "������� ���� ��� ������: ";
	dataSearch = Correct_Input();

	int i0 = 0, i1 = number_of_equipment - 1, m;
	while (i0 < i1) {
		m = (i1 + i0) / 2;
		if (arr_of_equipment[m].key > dataSearch) i0 = m + 1;
		else i1 = m;
	}
	if (arr_of_equipment[i0].key == dataSearch) cout << "��������� � ����� �����: " << arr_of_equipment[i0].name << endl;
	else cout << "����� ��������� ���\n";

}

void linearSearch(ticket* arr_of_equipment, int& number_of_equipment)
{
	readFileEquipment(arr_of_equipment, number_of_equipment);

	int dataSearch;
	bool k = false;

	cout << "������� ���� ��� ������: ";
	dataSearch = Correct_Input();

	for (int i = 0; i < number_of_equipment; i++)
	{
		if (arr_of_equipment[i].key == dataSearch) {
			k = true;
			cout << "��������� � ����� ����� � ������: " << arr_of_equipment[i].name << " " << arr_of_equipment[i].rdy << endl;
		}
	}
	if (k == false) cout << "����� ���� ���\n";
}

ticket* directSort(ticket* arr_of_equipment, int& number_of_equipment)
{
	readFileEquipment(arr_of_equipment, number_of_equipment);

	int i, j, m;
	for (i = 0; i < number_of_equipment - 1; i++)
	{
		m = i;
		for (j = i + 1; j < number_of_equipment; j++)
		{
			if (arr_of_equipment[j].key > arr_of_equipment[m].key) m = j;
		}
		ticket b = arr_of_equipment[i];
		arr_of_equipment[i] = arr_of_equipment[m];
		arr_of_equipment[m] = b;
	}
	return arr_of_equipment;
}

ticket* quickSort(ticket* arr_of_equipment, int& number_of_equipment)
{
	readFileEquipment(arr_of_equipment, number_of_equipment);

	int L = 0, R = number_of_equipment - 1, i, j;
	while (L != R) {
		while (L != R) {
			i = L;
			j = R;
			double m = arr_of_equipment[(i + j) / 2].key;
			while (i <= j)
			{
				while (arr_of_equipment[i].key > m)i++;
				while (arr_of_equipment[j].key < m)j--;
				if (i <= j)
				{
					ticket b = arr_of_equipment[i];
					arr_of_equipment[i] = arr_of_equipment[j];
					arr_of_equipment[j] = b;
					i++;
					j--;
				}
			}
			R--;
		}
		L++;
		R = number_of_equipment - 1;
	}
	return arr_of_equipment;
}

void tz(ticket* arr_of_equipment, int& number_of_equipment, int& number_of_strings)
{
	readFileEquipment(arr_of_equipment, number_of_equipment);
	//tzSort(arr_of_equipment, number_of_equipment, number_of_strings);
	showEquipmentArray(arr_of_equipment, number_of_equipment);
}