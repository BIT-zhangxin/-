#pragma once
#ifndef _MY_RANDOM
#define _MY_RANDOM

#include <time.h>

class RANDOM
{
private:

	//随机种子
	unsigned int maxdouble = 1073741824u;
	unsigned int multiplier = 1194211693u;
	unsigned int adder = 12345u;
	unsigned int randSeed = 0;

	//判断是否为二的次方数
	bool isIntegralPowerofTwo(int N)
	{
		for (int i = 1; i < 0x7fffffff / 3; i <<= 1)
		{
			if (N == i) return true;
		}
		return false;
	}

public:

	//默认构造函数
	RANDOM()
	{
		randSeed = (unsigned int)time(0);
	}

	//可以设定种子的构造函数
	RANDOM(unsigned int data)
	{
		randSeed = data;
	}

	//设置randSeed
	void SetrandSeed(unsigned int data)
	{
		randSeed = data;
	}

	//设置multiplier
	void Setmultiplier(unsigned int data)
	{
		multiplier = data;
	}

	//设置adder
	void Setadder(unsigned int data)
	{
		adder = data;
	}

	//设置maxshort
	void Setmaxshort(unsigned int data)
	{
		maxdouble = data;
	}

	//全部重置
	void Reset()
	{
		maxdouble = 1073741824u;
		multiplier = 1194211693u;
		adder = 12345u;
		randSeed = (unsigned int)time(0);
	}

	//取从0到edge-1之间的随机数（edge > 0）
	int Random(int edge)
	{
		randSeed = multiplier * randSeed + adder;
		if (isIntegralPowerofTwo(edge)) return (randSeed) % (3 * edge) / 3;
		//edge=2^n时会产生周期为edge的循环
		return (randSeed) % edge;
	}

	//取从left到right-1之间的随机数
	int Random(int left, int right)
	{
		if (left > right) return right + Random(left - right);
		return left + Random(right - left);
	}

	//取0到1之间的小数随机数
	double dRandom()
	{
		return Random(maxdouble) / double(maxdouble);
	}

	//取0到edge之间的小数随机数
	double dRandom(double edge)
	{
		return edge * dRandom();
	}

	//取left到right之间的小数随机数
	double dRandom(double left, double right)
	{
		if (left > right) return right + dRandom(left - right);
		return left + dRandom(right - left);
	}

	//将长度为N的Array数组用O(n)的交换算法打乱
	void Disorganize(int *Array, int N)
	{
		Random(N);//破坏循环
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
