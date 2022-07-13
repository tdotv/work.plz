#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Stack {
    char symbol;			// ������ ��������
    Stack* next;
};

int prior(char);
Stack* InS(Stack*, char);
Stack* OutS(Stack*, char&);
double result(Stack*, char*);
bool bracketCorrect(char*);
bool numberCorrect(char*);
bool checkString(char*);
bool operandCorrect(char*);

double correctInput()
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
            cin.clear(); // ������� ���� ������
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ���, ��� ��� ������������
            cout << "Oops, that input is invalid. Please try again.\n";
        }
    }
    return k;
}

const int MAX_CHARS = 256;

int main(Stack* top)
{
    setlocale(LC_ALL, "ru");
    Stack* t, * Op = NULL;  // ���� �������� Op � ����

    char symbol;
    char In[MAX_CHARS], Out[MAX_CHARS];
    int l = 0;   // ������� ������� ��� �����

    cout << " Input formula : ";
    do {
        cin.getline(In, MAX_CHARS - 1);
    } while (!checkString(In));

    for (int k = 0; In[k] != '\0'; k++)
    {
        if (In[k] >= 'a' && In[k] <= 'z')
            Out[l++] = In[k];   // �������� ���� ������
        else if (In[k] == '(')
            Op = InS(Op, In[k]);    // ������������ � ����
        else if (In[k] == ')') {
            while (Op->symbol != '(') {   // ���� � ��������� ������ c �� ����� (
                Op = OutS(Op, symbol);  // �������� � Op
                if (!Op) symbol = '\0';
                Out[l++] = symbol;
            }
            Op = OutS(Op, symbol);
        }
        else if (In[k] == '+' || In[k] == '-' || In[k] == '*' || In[k] == '/') {
            while (Op != NULL && prior(Op->symbol) >= prior(In[k])) {
                Op = OutS(Op, symbol);
                Out[l++] = symbol;
            }
            Op = InS(Op, In[k]);
        }
    }
    while (Op != NULL) {
        Op = OutS(Op, symbol);
        Out[l++] = symbol;
    }
    Out[l] = '\0';

    cout << "\n Polish = " << Out << endl;
    cout << "Res = " << result(top, Out) << endl;

    return 0;
}

int  prior(char a)
{
    switch (a) // ���� ��� ����� ����� ������, �� ���������� "���������"
    {
    case '*': 	case '/': 	return 3;
    case '-': 	case '+': 	return 2;
    case '(':   return 1;
    }
    return 0;
}

Stack* InS(Stack* p, char out)
{
    Stack* t = new Stack;
    t->symbol = out;
    t->next = p;
    return t;
}

Stack* OutS(Stack* p, char& in) // ������� ��������� Stack // ���������� �� �������
{
    Stack* t = p;
    in = p->symbol; // in ��������� ������ ������� � �������� �������� ��������� p �� ��������� c
    p = p->next; // ������ ��������� �� ����. �������
    delete t;
    return p;
}

double result(Stack* top, char* str)
{
    int  i;
    char ss, ss1, ss2, ssr = 'z' + 1, ssR = 'Z' + 1;
    double op1, op2, mas[256];
    double res = 0;
    cout << " Input data" << endl;
    for (i = 0; i < 256; i++)
        mas[i] = NULL;

    for (i = 0; str[i] != '\0'; ++i)
    {
        ss = str[i];

        if (ss >= 'a' && ss <= 'z') // ���� �����
        {
            if (mas[int(ss) - 'a'] == NULL) {
                cout << ss << " = ";
                mas[int(ss) - 'a'] = correctInput();    // ������ �������� �����
            }
        }
    }

    for (i = 0; str[i] != '\0'; ++i)
    {
        ss = str[i];
        if (!(ss == '+' || ss == '-' || ss == '*' || ss == '/'))
        {
            top = InS(top, ss);
        }
        else
        {
            top = OutS(top, ss2);
            top = OutS(top, ss1);
            op2 = mas[int(ss2) - 'a'];
            op1 = mas[int(ss1) - 'a'];

            switch (ss)
            {
            case'+': res = op1 + op2; break;
            case'-': res = op1 - op2; break;
            case'*': res = op1 * op2; break;
            case'/': if (op2 != 0) { res = op1 / op2; }
                   else { cout << "Attempt to divide by zero" << endl; exit(0); }   // �������� ������� �� 0
                   break;
            }
            mas[int(ssR) - 'a'] = res;
            top = InS(top, ssR);
            ssR++;
        }
    }
    return res;
}

// ========================= CHECK =================================

bool bracketCorrect(char* In)
{
    int open_bracket_count = 0, close_bracket_count = 0;

    for (int k = 0; In[k] != '\0'; k++)
    {
        if (In[k] == '(') open_bracket_count++;
        if (In[k] == ')') close_bracket_count++;
        if (In[0] == ')') open_bracket_count = -1;
        if (In[k] == '(')
            if (In[k + 1] == ')') open_bracket_count = -1;
    }
    if (open_bracket_count == close_bracket_count) return true;
    return false;
}

bool operandCorrect(char* In)
{
    int error = 0;
    for (int k = 0; In[k] != '\0'; k++)
    {
        if (In[k] >= 'a' && In[k] <= 'z')
        {
            if (In[k + 1] >= 'a' && In[k + 1] <= 'z')
                error++;
        }
            }
    if (error == 0) return true;
    return false;
}

bool numberCorrect(char* In)
{
    int operandCount = 0, operationCount = 0;

    for (int k = 0; In[k] != '\0'; k++)
    {
        if (In[k] >= 'a' && In[k] <= 'z')
            operandCount++;
        if (In[k] == '+' || In[k] == '-' || In[k] == '*' || In[k] == '/')
            operationCount++;
    }
    if (operandCount - operationCount == 1) return true;
    return false;
}

bool checkString(char* In)
{
    if (!bracketCorrect(In))
    {
        cout << "Bracket mistake" << endl;
        return false;
    }
    else if (!numberCorrect(In))
    {
        cout << "Operand or operation is missed" << endl;
        return false;
    }
    else if (!operandCorrect(In))
    {
        cout << "Check operand repeating" << endl;
        return false;
    }
    return true;
}