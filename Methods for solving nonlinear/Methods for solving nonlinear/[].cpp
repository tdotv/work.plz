#include <math.h>
#include <conio.h>
#include <iostream>

using namespace std;

double fun(double);
double bisectionMethod(double(*f)(double), double a, double b, double eps, int& k);
double secMethod(double(*f)(double), double x0, double eps, int& k);

double Correct_Input_Double()
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
            cin.clear(); //������� ���� ������
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); //���������� ���, ��� ��� ������������
            cout << "Oops, that input is invalid. Please try again.\n";
        }
    }
    return k;
}

int main()
{
    setlocale(LC_ALL, "rus");
    double x, y;
    int x0, x1, j = 0;
    int nom = 0;
    cout << "������� �������� ������ �������:" << endl;
    cout << "a = ";
    x0 = Correct_Input_Double();
    cout << "b = ";
    x1 = Correct_Input_Double();

    double h = 0;
    do
    {
        cout << "������� ���: ";
        h = Correct_Input_Double();
    } while (h > fabs(x0 - x1));    // ��� �� ������ ���� ������ ����� ������� ����������

    double eps = 0;
    do
    {
        cout << "������� �������� ����������, ��� ������ ���� ������ ����: ";
        eps = Correct_Input_Double();
    } while (eps >= h);

    for (x = x0; x < x1 + h / 4.; x += h)
    {               
        if (fun(x) * fun(x + h) < 0)    // ���� ���� ������� ����� ��� X
        {
            nom++;
            cout << "Interval:\n[" << x << ";" << x + h << "]" << endl;

            j = 0;
            y = bisectionMethod(fun, x, x + h, eps, j);  // ������� ������ � ������� ������� �������
            cout << "\nBisection method:\n" << "x = " << y << "\nNum of iterations: " << j << endl;
          
            j = 0;
            y = secMethod(fun, x, eps, j);   // ������� ������ � ������� ������ �������
            cout << "\Sec method:\n" << "x = " << y << "\nNum of iterations: " << j << endl;
            cout << endl;
        }
    }
    if (nom == 0) cout << ("�� ������� ������ ���!") << endl;

    system("pause");
    return 0;
}

double fun(double x) {
    return 0.1*x*x*x + x*x - 10*sin(x) - 8;   // [-4; 4]
}

double secMethod(double(*f)(double), double x0, double eps, int& k)   // ������� ������ �������
{
    int MAX_ITERATIONS = 100;//����������� �� ��������

    double h = eps * 10;
    double x1, de;
    double y0 = f(x0 - h);
    double y1 = f(x0);
    if (k > MAX_ITERATIONS) // ���� ������� �������� ������ ����������� ����������, �� ����� �� �����
    {
        cout << "���������� ����� � � �������� ���������!" << endl;
        return MAX_ITERATIONS;
    }
    else
    {
        do
        {
            x1 = x0 - y1 * h / (y1 - y0);
            de = fabs(x0 - x1);
            y0 = f(x1-h);
            y1 = f(x1);
            x0 = x1;
            ++k;
        } while (de >= eps || k < MAX_ITERATIONS);
    }
    return x1;
}

double bisectionMethod(double(*f)(double), double x0, double x1, double eps, int& k) // ������� ������ ������� �������
{
    int MAX_ITERATIONS = 100;//����������� �� ��������

    if (k > MAX_ITERATIONS)
    {
        cout << "���������� ����� � � �������� ���������!" << endl;
        return MAX_ITERATIONS;
    }
    double x = (x0 + x1) / 2.;
    if (fabs(x0 - x1) < eps)
        return x;
    else
    {
        if (f(x0) * f(x) < 0)
            x1 = x;  // ������ ������� = x
        else
            x0 = x;  // ����� �������
        return bisectionMethod(f, x0, x1, eps, ++k);
    }
}