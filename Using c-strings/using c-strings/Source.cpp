#include<iostream>
#include<cstring>
#include<conio.h>

using namespace std;
int main()
{
	int len_word = 0, pos = 0, i = 0;
	char str[256];
	cout << "Enter ur string : " << endl;
	cin.getline(str, 256);

	int len;
	len = strlen(str);
	cout << "Line length = " << len << endl;

	if (str[0] == '\0')
	{
		cout << "Ur string can't be created" << endl;
		exit(0);
	}

	if (str[len - 1] != ' ') { //если послледний не пробел
		strcat_s(str, " "); //добавляем строку-пробел
		len++;
	}

	int len_min = 1000;
	for (i = 0; i < len; i++)
	{
		if (str[i] != ' ') //если символ не пробел, увеличиваем длину слова
			len_word++;
		else //иначе, если - пробел
		{
			if (len_word < len_min)
			{
				len_min = len_word;
				pos = i - len_min;
			}
			len_word = 0;
		}
	}

	cout << "Minimal length = " << len_min << endl;
	cout << "Your minimal word is ";
	for (i = pos; i < pos + len_min; i++) cout << str[i];
}
