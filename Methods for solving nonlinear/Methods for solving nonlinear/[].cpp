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
            cin.clear(); //убираем флаг ошибки
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); //выкидываем все, что ввёл пользователь
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
    cout << "Введите значения концов отрезка:" << endl;
    cout << "a = ";
    x0 = Correct_Input_Double();
    cout << "b = ";
    x1 = Correct_Input_Double();

    double h = 0;
    do
    {
        cout << "Введите шаг: ";
        h = Correct_Input_Double();
    } while (h > fabs(x0 - x1));    // Шаг не должен быть больше самой области опрделения

    double eps = 0;
    do
    {
        cout << "Введите точность вычислений, она должна быть меньше шага: ";
        eps = Correct_Input_Double();
    } while (eps >= h);

    for (x = x0; x < x1 + h / 4.; x += h)
    {               
        if (fun(x) * fun(x + h) < 0)    // Если есть переход через ось X
        {
            nom++;
            cout << "Interval:\n[" << x << ";" << x + h << "]" << endl;

            j = 0;
            y = bisectionMethod(fun, x, x + h, eps, j);  // Находим корень с помощью деления пополам
            cout << "\nBisection method:\n" << "x = " << y << "\nNum of iterations: " << j << endl;
          
            j = 0;
            y = secMethod(fun, x, eps, j);   // Находим корень с помощью метода секущих
            cout << "\Sec method:\n" << "x = " << y << "\nNum of iterations: " << j << endl;
            cout << endl;
        }
    }
    if (nom == 0) cout << ("На отрезке корней НЕТ!") << endl;

    system("pause");
    return 0;
}

double fun(double x) {
    return 0.1*x*x*x + x*x - 10*sin(x) - 8;   // [-4; 4]
}

double secMethod(double(*f)(double), double x0, double eps, int& k)   // Функция метода секущих
{
    int MAX_ITERATIONS = 100;//ограничение на итерации

    double h = eps * 10;
    double x1, de;
    double y0 = f(x0 - h);
    double y1 = f(x0);
    if (k > MAX_ITERATIONS) // Если счетчик итераций больше допустимого количества, то выход из цикла
    {
        cout << "Невозможно найти Х с заданной точностью!" << endl;
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

double bisectionMethod(double(*f)(double), double x0, double x1, double eps, int& k) // Функция метода деления пополам
{
    int MAX_ITERATIONS = 100;//ограничение на итерации

    if (k > MAX_ITERATIONS)
    {
        cout << "Невохможно найти Х с заданной точностью!" << endl;
        return MAX_ITERATIONS;
    }
    double x = (x0 + x1) / 2.;
    if (fabs(x0 - x1) < eps)
        return x;
    else
    {
        if (f(x0) * f(x) < 0)
            x1 = x;  // Правая граница = x
        else
            x0 = x;  // Левая граница
        return bisectionMethod(f, x0, x1, eps, ++k);
    }
}