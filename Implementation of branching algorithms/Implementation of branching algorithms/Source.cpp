#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	double F, x, y;

	cout << "enter x=";
	cin >> x;

	cout << "enter y=";
	cin >> y;

	if (x >= 0 && y > 0)
	{
		cout << "x>=0, y>0" << endl;
		F = (2. * cos(x - (3.1415926535 / 6.)) + cbrt(y)) / (5. - 2. * x);
	}

	else
		if (x <= 0)
		{
			cout << "x<=0" << endl;
			F = min(0.9 * y, exp(2 * x - 3));
		}
		else
		{
			cout << "else" << endl;
			F = max(sin(y) * sin(y), cos(y) * cos(y));
		}
	cout << "F=" << F << endl;
	return 0;
}
