#include "QInt.h"


QInt::QInt()
{
	for (int i = 0; i < QINT_SIZE; i++)
	{
		arr[i] = 0;
	}
}

QInt::~QInt()
{

}
//Lay bit
bool QInt::getBit(int pos) const
{
	int bytePos = QINT_SIZE - 1 - pos / 32;
	int bitPos = pos % 32;
	return ((this->arr[bytePos] >> bitPos) & 1);
}

//Cap nhat vi tri bit
void QInt::setBit(int pos, bool value)
{
	int bytePos = QINT_SIZE - 1 - pos / 32;
	int bitPos = pos % 32;
	if (value)
	{
		this->arr[bytePos] = ((1 << bitPos) | this->arr[bytePos]);
	}
	else
	{
		this->arr[bytePos] = ((~(1 << bitPos)) & this->arr[bytePos]);
	}
}

//Nhap QInt theo co so
void QInt::scanQInt(string src, int base)
{
	int bitPos = 0;
	switch (base)
	{
	case 2:
		for (int i = src.length() - 1; i >= 0; i--)
		{
			setBit(bitPos, src[i] == '1');
			bitPos++;
		}
		break;
	case 10:
	{
		*this = decToBin(src);
		break;
	}
	case 16:
	{
		*this = hexToBin(src);
		break;
	}
	}
}

//Xuat QInt theo co so 2
void QInt::printQInt(int base)
{
	string res;
	res = CreateBinStr();
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	cout << res;
}

//Kiem tra so am
bool QInt::isNegative() const
{
	return ((this->getBit(QINT_SIZE * 32 - 1)) == 1);
}

// Tao ra mang 128 bit
string QInt::CreateBinStr() const
{
	string res = "";
	for (int i = 0; i < QINT_SIZE; i++)
	{
		res += bitset<32>(this->arr[i]).to_string();
	}
	return res;
}

string divByTwo(string src)
{
	string res = "";

	int add = 0;
	for (int i = 0; i < src.length(); i++)
	{
		int digit = src[i] - '0';
		res += ((digit / 2 + add) + '0');
		if (digit % 2 == 0)
			add = 0;
		else
			add = 5;
	}
	if (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}
QInt QInt::toInverse() const
{
	//Dao bit
	QInt res;
	for (int i = 0; i < QINT_SIZE; i++)
	{
		res.arr[i] = ~this->arr[i];
	}
	//Cong 1
	for (int i = QINT_SIZE - 1; i >= 0; i--)
	{
		if (res.arr[i] < 255)
		{
			res.arr[i] += 1;
			break;
		}
		else
			res.arr[i] = 0;
	}
	return res;
}

QInt QInt::decToBin(string src)
{
	QInt res;
	bool isNegative = false;
	if (src[0] == '-')
	{
		isNegative = true;
		src.erase(0, 1);
	}

	string binStr = "";
	do
	{
		int lastDigit = src[src.length() - 1] - '0';
		if (lastDigit % 2 == 0)
			binStr += '0';
		else
			binStr += '1';
		src = divByTwo(src);
	} while (src != "0");
	// Xuat bit theo thu tu nguoc lai.
	reverse(binStr.begin(), binStr.end());
	res.scanQInt(binStr, 2);
	if (isNegative == true)
	{
		res = res.toInverse();
	}
	return res;
}

QInt QInt::hexToBin(string src)
{
	bool isNegative = false;
	if (src[0] == '-')
	{
		isNegative = true;
		src.erase(0, 1);
	}
	QInt res;
	string binStr = "";
	for (int i = 0; i < src.length(); i++)
	{
		int pos = ((string)HEX_CHARS).find(src[i], 0);
		binStr += bitset<4>(pos).to_string();
	}
	res.scanQInt(binStr, 2);
	if (isNegative == true)
		res = res.toInverse();
	return res;
}

bool QInt::IsZero() const
{
	for (int i = 0; i < QINT_SIZE; i++)
	{
		if (arr[i] != 0)
			return false;
	}
	return true;
}

string QInt::multipleByTwo(string src, int add)
{
	string res = "";
	int carry = add;

	for (int i = src.length() - 1; i >= 0; i--)
	{
		int temp = src[i] - '0';
		temp = temp * 2 + carry;
		res += (temp % 10 + '0');
		carry = temp / 10;
	}
	if (carry > 0)
	{
		res += (carry + '0');
	}
	reverse(res.begin(), res.end());
	return res;
}
string QInt::binToDec(const QInt& src)
{
	string result;
	if (src.IsZero())
	{
		result = "0";
		return result;
	}
	QInt posSrc = src;
	if (src.isNegative())
	{
		posSrc = posSrc.toInverse();
	}
	string binStr = posSrc.CreateBinStr();
	int pos = binStr.find('1', 0) + 1;
	result = "1";
	while (pos < binStr.length())
	{
		int add = binStr[pos] - '0';
		result = multipleByTwo(result, add);
		pos++;
	}
	if (src.isNegative())
		result = '-' + result;
	return result;
}

QInt QInt::operator&(const QInt& x)
{
	QInt temp;
	for (int i = 0; i < 4; i++)
	{
		temp.arr[i] = this->arr[i] & x.arr[i];
	}
	return temp;
}

QInt QInt::operator|(const QInt& x)
{
	QInt temp;
	for (int i = 0; i < 4; i++)
	{
		temp.arr[i] = this->arr[i] | x.arr[i];
	}
	return temp;
}

QInt QInt::operator^(const QInt& x)
{
	QInt temp;
	for (int i = 0; i < 4; i++)
	{
		temp.arr[i] = this->arr[i] ^ x.arr[i];
	}
	return temp;
}

QInt QInt::operator~()
{
	QInt temp;
	for (int i = 0; i < 4; i++)
	{
		temp.arr[i] = ~this->arr[i];
	}
	return temp;
}

QInt QInt::operator<<(int x)
{
	QInt temp;
	string s = this->CreateBinStr();
	string s1;
	for (int i = 0; i < s.length(); i++)
	{
		if (i + (unsigned _int64)x >= s.length())
			s1 = s1 + '0';
		else
			s1 = s1 + s[i+(unsigned _int64)x];
	}
	temp.scanQInt(s1, 2);
	return temp;
}

QInt QInt::operator>>(int x)
{
	QInt temp;
	string s = this->CreateBinStr();
	string s1;
	for (int i = 0; i < s.length(); i++)
	{
		if (i < x)
			s1 = s1 + '0';
		else
		{
			s1 = s1+ s[i- (unsigned _int64)x];
		}
	}
	temp.scanQInt(s1, 2);
	return temp;
}

QInt QInt::rol(int x)
{
	QInt temp;
	char ch;
	string s = this->CreateBinStr();
	for (int i = 0; i < x; i++)
	{
		ch = s[0];
		for (int j = 0; j < s.length()-1; j++)
		{
				s[j] = s[(unsigned _int64)j + 1];
		}
		s[s.length() - 1] = ch;
	}
	temp.scanQInt(s, 2);
	return temp;
}

QInt QInt::ror(int x)
{
	QInt temp;
	char ch;
	string s = this->CreateBinStr();
	for (int i = 0; i < x; i++)
	{
		ch = s[s.length()-1];
		for (int j = 1; j < s.length(); j++)
		{
				s[j] = s[(unsigned _int64)j - 1];
		}
		s[0] = ch;
	}
	temp.scanQInt(s, 2);
	return temp;
}
