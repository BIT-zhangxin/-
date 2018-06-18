#pragma once
#ifndef _MY_PROBABILITYBOX
#define _MY_PROBABILITYBOX

#include "Random.h"

class ProbabilityBox
{
private:

	//�����
	RANDOM R;

	//�¼�����
	int EventNumber;

	//�¼�����
	double *Event;

public:

	//���캯��
	ProbabilityBox(int N)
	{
		EventNumber = N;
		Event = new double[EventNumber];
	}

	//��������
	~ProbabilityBox()
	{
		delete(Event);
	}

	//��ʼ������
	void Initialize(double *List)
	{
		for (int i = 0; i < EventNumber; i++)
		{
			Event[i] = List[i];
		}
	}

	//���ȡһ���¼�(��������)
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
