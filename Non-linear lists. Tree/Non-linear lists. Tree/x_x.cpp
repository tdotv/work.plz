#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

struct Tree {
	int info;
	string str;
	Tree* left, * right;
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

void Create_Array(Tree*, int&, int*, string*);
Tree* Create(Tree*);
Tree* EnterString(int);
void Add_List(Tree*, int);
Tree* Del(Tree*, int);
Tree* Find(Tree*, int);
void View(Tree*, int);
void View1(Tree*, int);
void View2(Tree*, int);
void View3(Tree*, int);
void Del_All(Tree*);
void Tree_Count(Tree*);
void Make_Balance(Tree**, int, int, int*, string*);
// Individual task
int CountRight(Tree* t);

int main()
{
	setlocale(LC_ALL, "rus");

	Tree* root = NULL, * p_min = NULL, * p_max = NULL, * t = NULL;
	int in, key, kod, i = 0;
	int arr[100];
	string s, ss[100];

	while (true)
	{
		do {
			cout << "\n========= ���� =========\n1 - �������� \n2 - ������������ \n3 - �������� \n4 - ����� �� ����� \n5 - ������� �� �����\n6 - ��������\n7 - �������������� ������� (���������� ���������� ������� � ������ ����� ������)\n0 - �����\n";
			kod = Correct_Input();
		}
		while (kod < 0 || kod > 7);

		switch (kod) {
		case 1:
		{
			if (root != NULL) {
				cout << "�������� ������!" << endl;
				break;
			}
			root = Create(root);
			break;
		}
		case 2:
		{
			if (root == NULL)
			{
				cout << "������ ��� �� ���� �������, ��������� � ����� 1 ��� ��������!" << endl; break;
			}
			Create_Array(root, i, arr, ss);
			Make_Balance(&root, 0, i, arr, ss);
			for (int j = 0; j < 100; j++)
				arr[j] = 0;
			i = 0;
			break;
		}
		case 3:
		{
			if (root == NULL)
			{
				cout << "������ ��� �� ���� �������, ��������� � ����� 1 ��� ��������!" << endl; break;
			}
			else
			{
				cout << "������� ����" << endl;
				in = Correct_Input();
				Add_List(root, in);
			}
			break;
		}
		case 4:
		{
			if (root == NULL)
			{
				cout << "������ ��� �� ���� �������, ��������� � ����� 1 ��� ��������!" << endl; break;
			}
			cout << "������� ����";
			key = Correct_Input();
			Find(root, key);
			break;
		}
		case 5:
		{
			if (root == NULL)
			{
				cout << "������ ��� �� ���� �������, ��������� � ����� 1 ��� ��������!" << endl; break;
			}
			cout << "������� ��������� ����: ";
			key = Correct_Input();
			root = Del(root, key);
			break;
		}
		case 6:
		{
			if (root == NULL)
			{
				cout << "������ ��� �� ���� �������, ��������� � ����� 1 ��� ��������!" << endl; break;
			}
			cout << "========= ������ =========" << endl;
			View(root, 0);
			cout << "�� �����������: " << endl;
			View2(root, 0);
			cout << "\n������-����-����� (���������� �����): " << endl;
			View1(root, 0);
			cout << "\n����-�����-������ (����������� �����): " << endl;
			View3(root, 0);
			break;
		}
		case 7:
		{
			if (root == NULL)
			{
				cout << "������ ��� �� ���� �������, ��������� � ����� 1 ��� ��������!" << endl; break;
			}
			cout << "� ������ ����� " << CountRight(root->right) << " ���������." << endl;
			break;
		}
		case 0:
		{
			return 0;
		}
		}
	}
	system("pause");
	system("cls");

	return 0;
}

void Create_Array(Tree* t, int& i, int* arr, string* s) {
	if (t) {
		Create_Array(t->left, i, arr, s);
		arr[i] = t->info;
		s[i] = t->str;
		cout << "arr[" << i << "] = " << t->info << "\tstr[" << i << "] = " << t->str << endl;
		i++;
		Create_Array(t->right, i, arr, s);
	}
}

Tree* Create(Tree* root) {
	Tree* Prev = NULL, * t;
	int b, find;
	if (!root) {
		cout << "������� ���� �����: ";
		b = Correct_Input();
		root = EnterString(b);
	}
	while (1) {
		cout << "������� ���� (������������� ����� - ��� ������): ";
		b = Correct_Input();
		if (b < 0) break;
		t = root;
		find = 0;
		while (t && !find) {
			Prev = t;
			if (b == t->info)
				find = 1; // ����� ������ ���� ���������
			else
				if (b < t->info) t = t->left;
				else   t = t->right;
		}
		if (find == 0){
			t = EnterString(b);
			if (b < Prev->info)
				Prev->left = t;
			else Prev->right = t;
		}
	}
	return root;
}

Tree* EnterString(int in)
{
	Tree* t = new Tree;
	t->info = in;
	cout << "������� ������: " << endl;
	getline(cin, t->str);
	t->left = t->right = NULL;
	return t;
}

void Add_List(Tree* root, int key)
{
	Tree* prev = NULL, * t = root;
	int find = 1;
	char str[101] = " ";
	while (t && find) {
		prev = t;
		if (key == t->info) {
			find = 0;
			cout << "���� �����������!" << endl;
		}
		else
			if (key < t->info) t = t->left;
			else t = t->right;
	}
	if (find) {
		t = EnterString(key);
		if (key < prev->info)
			prev->left = t;
		else
			prev->right = t;
	}
}

Tree* Del(Tree* root, int key) {
	Tree* Del = root, * Prev_Del = NULL, * R, * Prev_R;
	while (Del != NULL && Del->info != key) {
		Prev_Del = Del;
		if (Del->info > key) Del = Del->left;
		else Del = Del->right;
	}
	if (Del == NULL) {
		cout << "\n������ ����� ���!" << endl;
		return root;
	}
	if (Del->right == NULL) R = Del->left;
	else if (Del->left == NULL) R = Del->right;
	else { // ���� ����� ������ ���� � ����� ���������
		Prev_R = Del;
		R = Del->left;
		while (R->right != NULL) {
			Prev_R = R;
			R = R->right;
		}
		if (Prev_R == Del)
			R->right = Del->right;
		else {
			R->right = Del->right;
			Prev_R->right = R->left;
			R->left = Prev_R;
		}
	}
	if (Del == root) root = R;
	else if (Del->info < Prev_Del->info)
		Prev_Del->left = R;
	else Prev_Del->right = R;
	cout << "�������� ����� " << Del->info << " � �������: " << Del->str << endl;
	delete  Del;
	return root;
}

Tree* Find(Tree* root, int key) {
	Tree* find = root, * Prev_find = NULL;
	while (find != NULL && find->info != key) {
		Prev_find = find;
		if (find->info > key) find = find->left;
		else find = find->right;
	}
	if (find == NULL) {
		cout << "\n������ ����� ���!" << endl;
		return root;
	}
	cout << "������ �� ����� �����: " << find->str << endl;
	return root;
}

void View(Tree* t, int level) {
	if (t) {
		View(t->right, level + 1);
		for (int i = 0; i < level; i++)
			cout << "    ";
		cout << "__" << t->info << endl;
		View(t->left, level + 1);
	}
}

void View1(Tree* t, int level) { // ������ ����� ������ ���� �����
	if (t) {
		cout << "   " << t->info;
		View1(t->left, level + 1);
		View1(t->right, level + 1);
	}
}

void View2(Tree* t, int level) { // �� ����������� 
	if (t) {
		View2(t->left, level + 1);
		cout << "   " << t->info;
		View2(t->right, level + 1);
	}
}

void View3(Tree* t, int level) { // �������� ����� ���� ����� ������
	if (t) {
		View3(t->left, level + 1);
		View3(t->right, level + 1);
		cout << "   " << t->info;
	}
}

void Del_All(Tree* t) {
	if (t != NULL) {
		Del_All(t->left);
		Del_All(t->right);
		delete t;
	}
}

int CountRight(Tree* t)
{
	if (t == NULL)
	{
		return 0;
	}
	return 1 + CountRight(t->left) + CountRight(t->right);
}

void Make_Balance(Tree** p, int n, int k, int* a, string* s)
{
	if (n == k) {
		*p = NULL;
		return;
	}
	else {
		int m = (n + k) / 2;
		*p = new Tree;
		(*p)->info = a[m];
		(*p)->str = s[m];
		Make_Balance(&(*p)->left, n, m, a, s);
		Make_Balance(&(*p)->right, m + 1, k, a, s);
	}
}