#define _CRT_SECURE_NO_WARNINGS
#include "QInt.h"
#include <vector>
#include <sstream>
#include <conio.h>
void main()
{
	QInt a, b, c;
	a.scanQInt("296", 16);
	a.printQInt(2);
	cout << endl;
	b.scanQInt("-1534687", 10);
	b.printQInt(2);
	a& b;
	a.rol(1);
	a >> 2;
	cout << endl;
	string src = c.binToDec(a);
	cout << src;	
	system("pause");
}