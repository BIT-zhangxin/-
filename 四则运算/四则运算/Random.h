#pragma once
#ifndef _MY_RANDOM
#define _MY_RANDOM

#include <time.h>

class RANDOM
{
private:

	//�������
	unsigned int maxdouble = 1073741824u;
	unsigned int multiplier = 1194211693u;
	unsigned int adder = 12345u;
	unsigned int randSeed = 0;

	//�ж��Ƿ�Ϊ���Ĵη���
	bool isIntegralPowerofTwo(int N)
	{
		for (int i = 1; i < 0x7fffffff / 3; i <<= 1)
		{
			if (N == i) return true;
		}
		return false;
	}

public:

	//Ĭ�Ϲ��캯��
	RANDOM()
	{
		randSeed = (unsigned int)time(0);
	}

	//�����趨���ӵĹ��캯��
	RANDOM(unsigned int data)
	{
		randSeed = data;
	}

	//����randSeed
	void SetrandSeed(unsigned int data)
	{
		randSeed = data;
	}

	//����multiplier
	void Setmultiplier(unsigned int data)
	{
		multiplier = data;
	}

	//����adder
	void Setadder(unsigned int data)
	{
		adder = data;
	}

	//����maxshort
	void Setmaxshort(unsigned int data)
	{
		maxdouble = data;
	}

	//ȫ������
	void Reset()
	{
		maxdouble = 1073741824u;
		multiplier = 1194211693u;
		adder = 12345u;
		randSeed = (unsigned int)time(0);
	}

	//ȡ��0��edge-1֮����������edge > 0��
	int Random(int edge)
	{
		randSeed = multiplier * randSeed + adder;
		if (isIntegralPowerofTwo(edge)) return (randSeed) % (3 * edge) / 3;
		//edge=2^nʱ���������Ϊedge��ѭ��
		return (randSeed) % edge;
	}

	//ȡ��left��right-1֮��������
	int Random(int left, int right)
	{
		if (left > right) return right + Random(left - right);
		return left + Random(right - left);
	}

	//ȡ0��1֮���С�������
	double dRandom()
	{
		return Random(maxdouble) / double(maxdouble);
	}

	//ȡ0��edge֮���С�������
	double dRandom(double edge)
	{
		return edge * dRandom();
	}

	//ȡleft��right֮���С�������
	double dRandom(double left, double right)
	{
		if (left > right) return right + dRandom(left - right);
		return left + dRandom(right - left);
	}

	//������ΪN��Array������O(n)�Ľ����㷨����
	void Disorganize(int *Array, int N)
	{
		Random(N);//�ƻ�ѭ��
		for (int i = 0; i < N; i++)
		{
			Array[i] = i;
		}
		for (int i = 0; i < N; i++)
		{
			int loc = Random(i, N);
			int tmp = Array[i];
			Array[i] = Array[loc];
			Array[loc] = tmp;
		}
	}
};

#endif // !_MY_RANDOM
