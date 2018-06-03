#pragma once
#ifndef _MY_PROBABILITYBOX
#define _MY_PROBABILITYBOX

#include "Random.h"

class ProbabilityBox
{
private:

	//随机数
	RANDOM R;
	
	//事件个数
	int EventNumber;

	//事件概率
	double *Event;

public:

	//构造函数
	ProbabilityBox(int N)
	{
		EventNumber = N;
		Event = new double[EventNumber];
	}

	//析构函数
	~ProbabilityBox()
	{
		delete(Event);
	}

	//初始化概率
	void Initialize(double *List)
	{
		for (int i = 0; i < EventNumber; i++)
		{
			Event[i] = List[i];
		}
	}

	//随机取一个事件(返回其编号)
	int Draw()
	{
		double Sign = R.dRandom();
		double p = 0;
		for (int i = 0; i < EventNumber; i++)
		{
			if (p <= Sign && Sign < p + Event[i])
			{
				return i;
			}
			p += Event[i];
		}
		return EventNumber;
	}
};

#endif // !_MY_PROBABILITYBOX
