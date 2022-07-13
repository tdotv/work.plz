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
            cin.clear(); //убираем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //выкидываем все, что ввел пользователь
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
                cout << "Очередь уже существует! Если вы хотите создать новый список, нажмите 1, иначе - чтобы продолжить работу со старым" << endl;
                if (_getch() == '1')
                {
                    Delete(begin);
                }
                else
                    break;
            }
            cout << "Введите первый элемент очереди: ";
            in = Correct_Input();
            Create(begin, end, in);
            break;
        }
        case 2:
        {
            if (begin == NULL)
            {
                cout << "Очередь еще не создана. Вернитесь в пункт 1, чтобы создать ее" << endl; break;
            }
            else
            {
                cout << "Нажмите 1, чтобы заполнить очередь рандомом, иначе - чтобы заполнить вручную" << endl;
                if (_getch() == '1')
                {
                    cout << "Нажмите 1, чтобы добавить следующие элементы в начало списка, иначе - чтобы добавить в конец" << endl;
                    if (_getch() == '1')
                    {
                        cout << "Введите необходимое количество элементов = ";
                        int n = Correct_Input();

                        for (i = 1; i <= n; i++) {
                            in = (rand() % 201) - 100;
                            begin = AddBegin(begin, in);
                        }
                    }
                    else {
                        cout << "Введите необходимое количество элементов = ";
                        n = Correct_Input();

                        for (i = 1; i <= n; i++) {
                            in = (rand() % 201) - 100;
                            end = AddEnd(end, in);
                        } break;
                    }
                }
                else
                {
                    cout << "Нажмите 1, чтобы добавить следующие элементы в начало списка, иначе - чтобы добавить в начало" << endl;
                    if (_getch() == '1')
                    {
                        while (p == 0)
                        {
                            cout << "Введите элемент в очередь: ";
                            in = Correct_Input();
                            begin = AddBegin(begin, in);
                            cout << "Желаете продолжить?" << endl << " 0 - Да\n 1 - Нет\n";
                            cin >> p;
                        } p = 0; break;
                    }
                    else
                    {
                        while (p == 0)
                        {
                            cout << "Введите элемент в очередь: ";
                            in = Correct_Input();
                            begin = AddEnd(end, in);
                            cout << "Желаете продолжить?" << endl << "0 - Да\n 1 - Нет\n";
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
                cout << "Очередь еще не создана. Вернитесь в пункт 1, чтобы создать ее" << endl; break;
            }
            cout << "Список с начала:" << endl;
            ViewBegin(begin);
            cout << "Список с конца:" << endl;
            ViewEnd(end);
            break;
        }
        case 4:
        {
            Delete(begin);
            cout << "Память свободна!" << endl;
            break;
        }
        case 5:
        {
            Spisok* t = begin;
            if (begin == NULL)
            {
                cout << "Очередь пуста!" << endl;
                break;
            }
            while (t != NULL)
                if (DeleteOdd(begin, end) == NULL) {
                    cout << "Нечетных чисел нет!" << endl;
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
    cout << "Меню работы с очередью" << endl;
    cout << "1 - создать очередь" << endl;
    cout << "2 - добавить элемент" << endl;
    cout << "3 - показать содержимое списка" << endl;
    cout << "4 - удалить очередь" << endl;
    cout << "5 - выполнить индивидуальное задание" << endl;
    cout << "0 - завершить программу" << endl;
}

void Create(Spisok*& begin, Spisok*& end, int in)
{
    Spisok* t = new Spisok;
    t->info = in;   // формируем инф. часть
    t->next = t->prev = NULL;   // формируем адресные части
    begin = end = t;  // указатели на первый элемент
}

Spisok* AddBegin(Spisok* begin, int in)
{
    Spisok* t = new Spisok;
    t->prev = NULL; // предыдущего нет
    t->next = begin;    // связываем новый элемент с первым
    begin->prev = t;    // изменяем адрес бывшего первого
    begin = t;  // переставляем указатель на новый
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
        cout << "Очередь пуста!" << endl;
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
        cout << "Очередь пуста!" << endl;
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
            cout << "Удаляемый элемент = " << t->info << endl;
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
                    // изъятие элемента из списка
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