#pragma once
#include <iostream>
#include <string>
#include <bitset>
using namespace std;

#define QINT_SIZE 4
#define HEX_CHARS "0123456789ABCDEF"
class QInt
{
private:
	int arr[QINT_SIZE];
public:
	QInt();
	~QInt();
	void setBit(int pos, bool value);
	bool getBit(int pos) const;
	bool IsZero() const;
	void scanQInt(string src, int base);
	QInt toInverse() const;
	string CreateBinStr() const;
	void printQInt(int base);
	bool isNegative() const;
	QInt decToBin(string src);
	QInt hexToBin(string src);
	string multipleByTwo(string src, int add);
	string binToDec(const QInt& src);

	QInt operator & (const QInt& x);
	QInt operator | (const QInt& x);
	QInt operator ^ (const QInt& x);
	QInt operator ~ ();

	QInt operator <<(int x);
	QInt operator >>(int x);
	QInt rol(int x);
	QInt ror(int x);
};

