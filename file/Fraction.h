#pragma once
#ifndef _MY_FRACTION
#define _MY_FRACTION

#include <string>
#include <cstring>

class Fraction
{
public:

	int Numerator;//分子
	int Denominator;//分母

private:

	//通分化简
	void Simplificate()
	{
		if (Numerator == 0) Denominator = 0;
		if (Denominator < 0) Numerator = -Numerator;
		int Common_Divisor = Gcd((Numerator < 0) ? -Numerator : Numerator, Denominator);
		switch (Common_Divisor)
		{
		case 0:
			break;
		case 1:
			break;
		default:
			Numerator /= Common_Divisor;
			Denominator /= Common_Divisor;
			break;
		}
	}

	//求最小公因数
	int Gcd(int a, int b)
	{
		if (b == 0) return a;
		else return Gcd(b, a % b);
	}

	//将整形数字转化为字符串
	string IntoString(int Number)
	{
		string Tmp;
		bool isNegative = false;
		if (Number < 0)
		{
			Number = -Number;
			isNegative = true;
		}
		while (Number != 0)
		{
			char ch = Number % 10 + '0';
			Tmp = ch + Tmp;
			Number /= 10;
		}
		if (isNegative)
		{
			Tmp = '-' + Tmp;
		}
		return Tmp;
	}

public:

	//赋零
	Fraction()
	{
		Numerator = 0;
		Denominator = 0;
		Simplificate();
	}

	//设为整数
	Fraction(int Integer)
	{
		Numerator = Integer;
		Denominator = 1;
		Simplificate();
	}

	//设为分数
	Fraction(int Numerator, int Denominator)
	{
		this->Numerator = Numerator;
		this->Denominator = Denominator;
		Simplificate();
	}

public:

	//判断是否为零
	bool isZero()
	{
		return Numerator == 0;
	}

	//判断是否为整数
	bool isInteger()
	{
		if (isZero())
			return true;
		else
			return Denominator == 1;
	}

	//如果是整数返回整数，否则返回零
	int Integer()
	{
		if (isInteger())
			return Numerator;
		else
			return 0;
	}

	//返回double类型的小数值
	double Double()
	{
		if (isZero())
			return 0;
		else
			return (double)Numerator / (double)Denominator;
	}

	//返回字符串，负数加括号
	string String()
	{
		string Tmp;
		bool isNegative = false;
		if (Denominator == 1)
		{
			Tmp += IntoString(Numerator);
		}
		else
		{
			Tmp += IntoString(Numerator);
			Tmp += '/';
			Tmp += IntoString(Denominator);
		}
		return Tmp;
	}

public:
	//重载运算符

	//负号
	Fraction operator -()
	{
		return Fraction(-Numerator, Denominator);
	}

	//逻辑运算符

	friend bool operator == (Fraction A, Fraction B)
	{
		if (A.Numerator == B.Numerator&&A.Denominator == B.Denominator)
			return true;
		else
			return false;
	}

	friend bool operator != (Fraction A, Fraction B)
	{
		return !(A == B);
	}

	friend bool operator < (Fraction A, Fraction B)
	{
		return A.Double() < B.Double();
	}

	friend bool operator > (Fraction A, Fraction B)
	{
		return A.Double() > B.Double();
	}

	friend bool operator <= (Fraction A, Fraction B)
	{
		return A.Double() <= B.Double();
	}

	friend bool operator >= (Fraction A, Fraction B)
	{
		return A.Double() >= B.Double();
	}

	//加法

	//Fraction operator + (Fraction Operand)
	//{
	//	if (isZero())
	//		return Operand;
	//	else if (Operand.isZero())
	//		return *this;
	//	else if (Denominator == Operand.Denominator)
	//		return Fraction(Numerator + Operand.Numerator, Denominator);
	//	else
	//	{
	//		Fraction tmp;
	//		tmp.Denominator = Denominator * Operand.Denominator;
	//		tmp.Numerator = Numerator * Operand.Denominator + Denominator * Operand.Numerator;
	//		tmp.Simplificate();
	//		return tmp;
	//	}
	//}

	friend Fraction operator + (Fraction A, Fraction B)
	{
		if (A.isZero())
			return B;
		else if (B.isZero())
			return A;
		else if (A.Denominator == B.Denominator)
			return Fraction(A.Numerator + B.Numerator, A.Denominator);
		else
		{
			Fraction tmp;
			tmp.Denominator = A.Denominator * B.Denominator;
			tmp.Numerator = A.Numerator * B.Denominator + A.Denominator * B.Numerator;
			tmp.Simplificate();
			return tmp;
		}
	}

	friend Fraction operator + (Fraction A, int B)
	{
		if (A.isZero())
			return Fraction(B);
		else if (B == 0)
			return A;
		else
		{
			Fraction tmp;
			tmp.Denominator = A.Denominator;
			tmp.Numerator = A.Numerator + A.Denominator * B;
			tmp.Simplificate();
			return tmp;
		}
	}

	friend Fraction operator + (int A, Fraction B)
	{
		if (A == 0)
			return B;
		else if (B.isZero())
			return Fraction(A);
		else
		{
			Fraction tmp;
			tmp.Denominator = B.Denominator;
			tmp.Numerator = A * B.Denominator + B.Numerator;
			tmp.Simplificate();
			return tmp;
		}
	}

	//减法

	//Fraction operator - (Fraction Operand)
	//{
	//	if (isZero())
	//		return -Operand;
	//	else if (Operand.isZero())
	//		return *this;
	//	else if (Denominator == Operand.Denominator)
	//		return Fraction(Numerator - Operand.Numerator, Denominator);
	//	else
	//	{
	//		Fraction tmp;
	//		tmp.Denominator = Denominator * Operand.Denominator;
	//		tmp.Numerator = Numerator * Operand.Denominator - Denominator * Operand.Numerator;
	//		tmp.Simplificate();
	//		return tmp;
	//	}
	//}

	friend Fraction operator - (Fraction A, Fraction B)
	{
		if (A.isZero())
			return -B;
		else if (B.isZero())
			return A;
		else if (A.Denominator == B.Denominator)
			return Fraction(A.Numerator - B.Numerator, A.Denominator);
		else
		{
			Fraction tmp;
			tmp.Denominator = A.Denominator * B.Denominator;
			tmp.Numerator = A.Numerator * B.Denominator - A.Denominator * B.Numerator;
			tmp.Simplificate();
			return tmp;
		}
	}

	friend Fraction operator - (Fraction A, int B)
	{
		if (A.isZero())
			return Fraction(-B);
		else if (B == 0)
			return A;
		else
		{
			Fraction tmp;
			tmp.Denominator = A.Denominator;
			tmp.Numerator = A.Numerator - A.Denominator * B;
			tmp.Simplificate();
			return tmp;
		}
	}

	friend Fraction operator - (int A, Fraction B)
	{
		if (A == 0)
			return -B;
		else if (B.isZero())
			return Fraction(A);
		else
		{
			Fraction tmp;
			tmp.Denominator = B.Denominator;
			tmp.Numerator = A * B.Denominator - B.Numerator;
			tmp.Simplificate();
			return tmp;
		}
	}

	//乘法

	//Fraction operator * (Fraction Operand)
	//{
	//	if (isZero())
	//		return *this;
	//	else if (Operand.isZero())
	//		return Operand;
	//	else
	//	{
	//		Fraction tmp;
	//		tmp.Denominator = Denominator * Operand.Denominator;
	//		tmp.Numerator = Numerator  * Operand.Numerator;
	//		tmp.Simplificate();
	//		return tmp;
	//	}
	//}

	friend Fraction operator * (Fraction A, Fraction B)
	{
		if (A.isZero())
			return A;
		else if (B.isZero())
			return B;
		else
		{
			Fraction tmp;
			tmp.Denominator = A.Denominator * B.Denominator;
			tmp.Numerator = A.Numerator * B.Numerator;
			tmp.Simplificate();
			return tmp;
		}
	}

	friend Fraction operator * (Fraction A, int B)
	{
		if (A.isZero())
			return A;
		else if (B == 0)
			return Fraction();
		else
		{
			Fraction tmp;
			tmp.Denominator = A.Denominator;
			tmp.Numerator = A.Numerator * B;
			tmp.Simplificate();
			return tmp;
		}
	}

	friend Fraction operator * (int A, Fraction B)
	{
		if (A == 0)
			return Fraction();
		else if (B.isZero())
			return B;
		else
		{
			Fraction tmp;
			tmp.Denominator = B.Denominator;
			tmp.Numerator = A * B.Numerator;
			tmp.Simplificate();
			return tmp;
		}
	}

	//除法

	/*Fraction operator / (Fraction Operand)
	{
	if (Operand.isZero())
	throw 0;
	else if (isZero())
	return *this;*/
	//	else
	//	{
	//		Fraction tmp;
	//		tmp.Denominator = Denominator * Operand.Numerator;
	//		tmp.Numerator = Numerator * Operand.Denominator;
	//		tmp.Simplificate();
	//		return tmp;
	//	}
	//}

	friend Fraction operator / (Fraction A, Fraction B)
	{
		if (B.isZero())
			throw 0;
		else if (A.isZero())
			return A;
		else
		{
			Fraction tmp;
			tmp.Denominator = A.Denominator * B.Numerator;
			tmp.Numerator = A.Numerator * B.Denominator;
			tmp.Simplificate();
			return tmp;
		}
	}

	friend Fraction operator / (Fraction A, int B)
	{
		if (B == 0)
			throw 0;
		else if (A.isZero())
			return A;
		else
		{
			Fraction tmp;
			tmp.Denominator = A.Denominator * B;
			tmp.Numerator = A.Numerator;
			tmp.Simplificate();
			return tmp;
		}
	}

	friend Fraction operator / (int A, Fraction B)
	{
		if (B.isZero())
			throw 0;
		else if (A == 0)
			return Fraction();
		else
		{
			Fraction tmp;
			tmp.Denominator = B.Numerator;
			tmp.Numerator = A * B.Denominator;
			tmp.Simplificate();
			return tmp;
		}
	}

	//乘方

	//Fraction operator ^ (int Operand)
	//{
	//	if (Operand == 0 && isZero())
	//		throw 0;
	//	else if (Operand == 0)
	//		return Fraction(1);
	//	else if (isZero())
	//		return Fraction();
	//	else
	//	{
	//		Fraction tmp(1);
	//		while (Operand--)
	//		{
	//			tmp = tmp * (*this);
	//		}
	//		return tmp;
	//	}
	//}

	friend Fraction operator ^ (Fraction A, int B)
	{
		if (A.isZero() && B == 0)
			throw 0;
		else if (A.isZero())
			return Fraction();
		else if (B == 0)
			return Fraction(1);
		else
		{
			Fraction tmp(1);
			while (B--)
			{
				tmp = tmp * A;
			}
			return tmp;
		}
	}

};

#endif // !_MY_FRACTION
