#include <conio.h>
#include <iostream>

using namespace std;

struct Spisok {
    int info;
    Spisok* prev, * next;
};

void menu();
void Create(Spisok*& begin, Spisok*& end, int in);
Spisok* AddBegin(Spisok*, int);
Spisok* AddEnd(Spisok*, int);
void ViewBegin(Spisok* begin);
void ViewEnd(Spisok* end);
Spisok* Delete(Spisok*& begin);
Spisok* DeleteOdd(Spisok*& begin, Spisok*& end);

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //���������� ���, ��� ���� ������������
            cout << "Oops, that input is invalid. Please try again.\n";
        }
    }
    return k;
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    int i, in, n = 0;
    Spisok* begin = NULL;
    Spisok* end = NULL;
    bool flag_exit = true, p = 0;
    while (flag_exit)
    {
        menu();
        int kod = Correct_Input();
        switch (kod)
        {
        case 0: flag_exit = false; break;
        case 1:
        {
            if (begin != NULL) {
                cout << "������� ��� ����������! ���� �� ������ ������� ����� ������, ������� 1, ����� - ����� ���������� ������ �� ������" << endl;
                if (_getch() == '1')
                {
                    Delete(begin);
                }
                else
                    break;
            }
            cout << "������� ������ ������� �������: ";
            in = Correct_Input();
            Create(begin, end, in);
            break;
        }
        case 2:
        {
            if (begin == NULL)
            {
                cout << "������� ��� �� �������. ��������� � ����� 1, ����� ������� ��" << endl; break;
            }
            else
            {
                cout << "������� 1, ����� ��������� ������� ��������, ����� - ����� ��������� �������" << endl;
                if (_getch() == '1')
                {
                    cout << "������� 1, ����� �������� ��������� �������� � ������ ������, ����� - ����� �������� � �����" << endl;
                    if (_getch() == '1')
                    {
                        cout << "������� ����������� ���������� ��������� = ";
                        int n = Correct_Input();

                        for (i = 1; i <= n; i++) {
                            in = (rand() % 201) - 100;
                            begin = AddBegin(begin, in);
                        }
                    }
                    else {
                        cout << "������� ����������� ���������� ��������� = ";
                        n = Correct_Input();

                        for (i = 1; i <= n; i++) {
                            in = (rand() % 201) - 100;
                            end = AddEnd(end, in);
                        } break;
                    }
                }
                else
                {
                    cout << "������� 1, ����� �������� ��������� �������� � ������ ������, ����� - ����� �������� � ������" << endl;
                    if (_getch() == '1')
                    {
                        while (p == 0)
                        {
                            cout << "������� ������� � �������: ";
                            in = Correct_Input();
                            begin = AddBegin(begin, in);
                            cout << "������� ����������?" << endl << " 0 - ��\n 1 - ���\n";
                            cin >> p;
                        } p = 0; break;
                    }
                    else
                    {
                        while (p == 0)
                        {
                            cout << "������� ������� � �������: ";
                            in = Correct_Input();
                            begin = AddEnd(end, in);
                            cout << "������� ����������?" << endl << "0 - ��\n 1 - ���\n";
                            cin >> p;
                        }
                        p = 0;
                        break;
                    }
                }
                break;
            }
        }
        case 3:
        {
            if (begin == NULL)
            {
                cout << "������� ��� �� �������. ��������� � ����� 1, ����� ������� ��" << endl; break;
            }
            cout << "������ � ������:" << endl;
            ViewBegin(begin);
            cout << "������ � �����:" << endl;
            ViewEnd(end);
            break;
        }
        case 4:
        {
            Delete(begin);
            cout << "������ ��������!" << endl;
            break;
        }
        case 5:
        {
            Spisok* t = begin;
            if (begin == NULL)
            {
                cout << "������� �����!" << endl;
                break;
            }
            while (t != NULL)
                if (DeleteOdd(begin, end) == NULL) {
                    cout << "�������� ����� ���!" << endl;
                    break;
                }
            break;
        }
        }
        system("pause");
        system("cls");
    }
}

void menu()
{
    cout << "���� ������ � ��������" << endl;
    cout << "1 - ������� �������" << endl;
    cout << "2 - �������� �������" << endl;
    cout << "3 - �������� ���������� ������" << endl;
    cout << "4 - ������� �������" << endl;
    cout << "5 - ��������� �������������� �������" << endl;
    cout << "0 - ��������� ���������" << endl;
}

void Create(Spisok*& begin, Spisok*& end, int in)
{
    Spisok* t = new Spisok;
    t->info = in;   // ��������� ���. �����
    t->next = t->prev = NULL;   // ��������� �������� �����
    begin = end = t;  // ��������� �� ������ �������
}

Spisok* AddBegin(Spisok* begin, int in)
{
    Spisok* t = new Spisok;
    t->prev = NULL; // ����������� ���
    t->next = begin;    // ��������� ����� ������� � ������
    begin->prev = t;    // �������� ����� ������� �������
    begin = t;  // ������������ ��������� �� �����
    t->info = in;
    return t;
}

Spisok* AddEnd(Spisok* end, int in)
{
    Spisok* t = new Spisok;
    t->next = NULL;
    t->prev = end;
    end->next = t;
    end = t;
    t->info = in;
    return t;
}

void ViewBegin(Spisok* begin)
{
    Spisok* t = begin;
    if (begin == NULL)
    {
        cout << "������� �����!" << endl;
        return;
    }
    while (t != NULL)
    {
        cout << t->info << " ";
        t = t->next;
    }
    cout << endl;
}

void ViewEnd(Spisok* end)
{
    Spisok* t = end;
    if (end == NULL)
    {
        cout << "������� �����!" << endl;
        return;
    }
    while (t != NULL)
    {
        cout << t->info << " ";
        t = t->prev;
    }
    cout << endl;
}

Spisok* Delete(Spisok*& begin)
{
    Spisok* t;
    while (begin)
    {
        t = begin;
        begin = begin->next;
        delete t;
    }
    return 0;
}

Spisok* DeleteOdd(Spisok*& begin, Spisok*& end)
{
    Spisok* t, * key = NULL;
    t = begin;
    while (t != NULL)
    {
        if (t->info % 2 != 0)
        {
            key = t;
            cout << "��������� ������� = " << t->info << endl;
            if (key == begin)
            {
                begin = begin->next;
                if (begin != NULL) begin->prev = NULL;
                else begin = end = NULL;
            }
            else {
                if (key == end)
                {
                    end = end->prev;
                    end->next = NULL;
                }
                else
                {
                    // ������� �������� �� ������
                    (key->prev)->next = key->next;
                    (key->next)->prev = key->prev;
                }
            }
            delete key;
            break;
        }
        else t = t->next;
    }
    return key;
}