#pragma once
#ifndef _MY_FRACTION
#define _MY_FRACTION

#include <string>
#include <cstring>

class Fraction
{
private:

	int Numerator;//����
	int Denominator;//��ĸ

private:

	//ͨ�ֻ���
	void Simplificate()
	{
		if (Numerator == 0) Denominator = 0;
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

	//����С������
	int Gcd(int a, int b)
	{
		if (b == 0) return a;
		else return Gcd(b, a % b);
	}

	//����������ת��Ϊ�ַ���
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

	//����
	Fraction()
	{
		Numerator = 0;
		Denominator = 0;
		Simplificate();
	}

	//��Ϊ����
	Fraction(int Integer)
	{
		Numerator = Integer;
		Denominator = 1;
		Simplificate();
	}

	//��Ϊ����
	Fraction(int Numerator, int Denominator)
	{
		this->Numerator = Numerator;
		this->Denominator = Denominator;
		Simplificate();
	}

public:

	//�ж��Ƿ�Ϊ��
	bool isZero()
	{
		return Numerator == 0;
	}

	//�ж��Ƿ�Ϊ����
	bool isInteger()
	{
		if (isZero())
			return true;
		else
			return Denominator == 1;
	}

	//����������������������򷵻���
	int Integer()
	{
		if (isInteger())
			return Numerator;
		else
			return 0;
	}

	//����double���͵�С��ֵ
	double Double()
	{
		if (isZero())
			return 0;
		else
			return (double)Numerator / (double)Denominator;
	}

	//�����ַ���������������
	string String()
	{
		string Tmp;
		bool isNegative = false;
		if (Numerator < 0) isNegative = true;
		if (isNegative)
		{
			Tmp += '(';
		}
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
		if (isNegative)
		{
			Tmp += ')';
		}
		return Tmp;
	}

public:
	//���������

	//����
	Fraction operator -()
	{
		return Fraction(-Numerator, Denominator);
	}

	//�߼������

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

	//�ӷ�

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

	//����

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

	//�˷�

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

	//�˷�

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
		else if (A.isZero() == 0)
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