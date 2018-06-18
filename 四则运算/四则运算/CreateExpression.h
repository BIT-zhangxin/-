#pragma once
#ifndef _MY_CREATEEXPRESSION
#define _MY_CREATEEXPRESSION

#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include "Random.h"
#include "Linklist.h"
#include "Fraction.h"
#include "ProbabilityBox.h"
using namespace std;

class CreateExpression
{
private:

	class Container
	{
	public:

		//��������
		int Parameter_Number;

		//����
		LINKLIST<Fraction *>List;

		//���캯��������ָ����������
		Container(int N)
		{
			Parameter_Number = N;
		}

		//����������Ԫ�ظ���
		int Length()
		{
			return List.length();
		}

		//��������
		void Push(Fraction *Parameter)
		{
			List.push(Parameter);
		}

		//����Ƿ��ظ�
		bool Check(Fraction *Parameter)
		{
			for (int i = 0; i < List.length(); i++)
			{
				if (Compare(List.visit(i), Parameter)) return true;
			}
			return false;
		}

	private:

		//�Ƚ�����ʽ�ӵĲ���
		bool Compare(Fraction *Parameter1, Fraction *Parameter2)
		{
			for (int i = 0; i < Parameter_Number; i++)
			{
				if (Parameter1[i] != Parameter2[i]) return false;
			}
			return true;
		}
	};

	//�����
	RANDOM R;

	//���ɱ��ʽ����
	int Expression_Number = 0;

	//�����ɵ�ʽ�Ӹ���
	int Now_Number = 0;

	//���ʽ
	string Expression[1000];

	//n����ʽ�ӵĸ���
	int Expression_Parameter_Number[8] = { 0 };

	//�������
	int Disorganize_List[1000] = { 0 };

	//���ʺ���
	ProbabilityBox Parameter_Probability_Box;
	double Parameter_Probability_List[8] = { 0,0,0.02,0.22,0.40,0.28,0.04,0.04 };
	ProbabilityBox Integer_Probability_Box;
	double Integer_Probability_List[2] = { 0.7,0.3 };//0.7Ϊ������0.3Ϊ����
	ProbabilityBox Positive_Number_Probability_Box;
	double Positive_Number_Probability_List[2] = { 1,0 };//0.9Ϊ������0.1Ϊ����
	ProbabilityBox Data_Range_Probability_Box;
	double Data_Range_Probability_List[3] = { 0.8,0.15,0.05 };//0.8Ϊ2��29��0.15Ϊ30��79��0.05Ϊ80��200
	ProbabilityBox Sign_Probability_Box;
	double Sign_Probability_List[4] = { 0.25,0.25,0.25,0.25 };

public:

	//���캯��

	//�޲������캯��
	CreateExpression() :
		Parameter_Probability_Box(8),
		Integer_Probability_Box(2),
		Positive_Number_Probability_Box(2),
		Data_Range_Probability_Box(3),
		Sign_Probability_Box(4)
	{
		Expression_Number = 1000;
		Initialize();
	}

	CreateExpression(const char *address) :
		Parameter_Probability_Box(8),
		Integer_Probability_Box(2),
		Positive_Number_Probability_Box(2),
		Data_Range_Probability_Box(3),
		Sign_Probability_Box(4)
	{
		Expression_Number = 1000;
		Initialize();
		Create();
		FILE *fp = fopen(address, "w");
		if (fp == NULL)
		{
			printf("ERROR\n");
			return;
		}
		for (int i = 0; i < Expression_Number; i++)
		{
			char tmp[100] = { 0 };
			strcpy_s(tmp, Expression[i].c_str());
			fputs(tmp, fp);
			fputc('\n', fp);
		}
		fclose(fp);
	}

private:

	//��ʼ������
	void Initialize()
	{
		R.Disorganize(Disorganize_List, Expression_Number);
		Parameter_Probability_Box.Initialize(Parameter_Probability_List);
		for (int i = 0; i < Expression_Number; i++)
		{
			Expression_Parameter_Number[Parameter_Probability_Box.Draw()]++;
		}
		Integer_Probability_Box.Initialize(Integer_Probability_List);
		Positive_Number_Probability_Box.Initialize(Positive_Number_Probability_List);
		Data_Range_Probability_Box.Initialize(Data_Range_Probability_List);
		Sign_Probability_Box.Initialize(Sign_Probability_List);
	}

	//��������
	int Create_Integer()
	{
		int Tmp = 0;
		switch (Data_Range_Probability_Box.Draw())
		{
		case 0:
			Tmp = R.Random(2, 10);
			break;
		case 1:
			Tmp = R.Random(10, 20);
			break;
		case 2:
			Tmp = R.Random(20, 30);
			break;
		}
		return Tmp;
	}

	//��������
	Fraction Create_Fraction()
	{
		Fraction Tmp;
		switch (Integer_Probability_Box.Draw())
		{
		case 0:
			Tmp = Fraction(Create_Integer(), 1);
			break;
		case 1:
			Tmp = Fraction(Create_Integer(), Create_Integer());
			break;
		}
		switch (Positive_Number_Probability_Box.Draw())
		{
		case 0:
			break;
		case 1:
			Tmp = -Tmp;
			break;
		}
		return Tmp;
	}

	//��������
	char Create_Sign()
	{
		char Tmp;
		switch (Sign_Probability_Box.Draw())
		{
		case 0:
			Tmp = '+';
			break;
		case 1:
			Tmp = '-';
			break;
		case 2:
			Tmp = '*';
			break;
		case 3:
			Tmp = '/';
			break;
		}
		return Tmp;
	}

	//�������ʽ
	string Create_Expression(Fraction *List, int N)
	{
		string Tmp;
		int *A = new int[N];
		R.Disorganize(A, N);
		for (int i = 0; i < N; i++)
		{
			Tmp += List[A[i]].String();
			if (i != N - 1)
			{
				Tmp += ' ';
				Tmp += Create_Sign();
				Tmp += ' ';
			}
		}
		return Tmp;
	}

	//����N�����ı��ʽ
	void Create_Parameter(int N)
	{
		Container container(N);
		while (container.Length() < Expression_Parameter_Number[N])
		{
			Fraction *List = new Fraction[N];
			for (int i = 0; i < N; i++)
			{
				List[i] = Create_Fraction();
			}
			for (int i = 0; i < N; i++)
			{
				Fraction Min = List[i];
				int MinLoc = i;
				for (int j = i + 1; j < N; j++)
				{
					if (List[j] < Min)
					{
						Min = List[j];
						MinLoc = j;
					}
				}
				List[MinLoc] = List[i];
				List[i] = Min;
			}
			if (!container.Check(List))
			{
				container.Push(List);
			}
		}
		int *A = new int[Expression_Parameter_Number[N]];
		R.Disorganize(A, Expression_Parameter_Number[N]);
		for (int i = 0; i < Expression_Parameter_Number[N]; i++)
		{
			Expression[Disorganize_List[Now_Number++]] = Create_Expression(container.List.visit(i), N);
		}
	}

public:

	//�������еı��ʽ
	void Create()
	{
		for (int i = 2; i <= 7; i++)
		{
			Create_Parameter(i);
		}
	}

	//��ӡ���е�ʽ��
	void Print()
	{
		for (int i = 0; i < Expression_Number; i++)
		{
			cout << Expression[i] << endl;
		}
	}

};

#endif // !_MY_CREATEEXPRESSION
