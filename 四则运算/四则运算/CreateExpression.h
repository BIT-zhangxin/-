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

		//参数个数
		int Parameter_Number;

		//链表
		LINKLIST<Fraction *>List;

		//构造函数，必须指定参数个数
		Container(int N)
		{
			Parameter_Number = N;
		}

		//返回链表中元素个数
		int Length()
		{
			return List.length();
		}

		//推入链表
		void Push(Fraction *Parameter)
		{
			List.push(Parameter);
		}

		//检查是否重复
		bool Check(Fraction *Parameter)
		{
			for (int i = 0; i < List.length(); i++)
			{
				if (Compare(List.visit(i), Parameter)) return true;
			}
			return false;
		}

	private:

		//比较两个式子的参数
		bool Compare(Fraction *Parameter1, Fraction *Parameter2)
		{
			for (int i = 0; i < Parameter_Number; i++)
			{
				if (Parameter1[i] != Parameter2[i]) return false;
			}
			return true;
		}
	};

	//随机数
	RANDOM R;

	//生成表达式个数
	int Expression_Number = 0;

	//已生成的式子个数
	int Now_Number = 0;

	//表达式
	string Expression[1000];

	//n参数式子的个数
	int Expression_Parameter_Number[8] = { 0 };

	//随机序列
	int Disorganize_List[1000] = { 0 };

	//概率盒子
	ProbabilityBox Parameter_Probability_Box;
	double Parameter_Probability_List[8] = { 0,0,0.02,0.22,0.40,0.28,0.04,0.04 };
	ProbabilityBox Integer_Probability_Box;
	double Integer_Probability_List[2] = { 0.7,0.3 };//0.7为整数，0.3为分数
	ProbabilityBox Positive_Number_Probability_Box;
	double Positive_Number_Probability_List[2] = { 1,0 };//0.9为正数，0.1为负数
	ProbabilityBox Data_Range_Probability_Box;
	double Data_Range_Probability_List[3] = { 0.8,0.15,0.05 };//0.8为2到29，0.15为30到79，0.05为80到200
	ProbabilityBox Sign_Probability_Box;
	double Sign_Probability_List[4] = { 0.25,0.25,0.25,0.25 };

public:

	//构造函数

	//无参数构造函数
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

	//初始化函数
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

	//创建整数
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

	//创建分数
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

	//创建符号
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

	//创建表达式
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

	//创建N参数的表达式
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

	//创立所有的表达式
	void Create()
	{
		for (int i = 2; i <= 7; i++)
		{
			Create_Parameter(i);
		}
	}

	//打印所有的式子
	void Print()
	{
		for (int i = 0; i < Expression_Number; i++)
		{
			cout << Expression[i] << endl;
		}
	}

};

#endif // !_MY_CREATEEXPRESSION
