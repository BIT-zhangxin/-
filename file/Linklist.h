#pragma once
#ifndef _MY_LINKLIST
#define _MY_LINKLIST

template<typename Type>
class LINKLIST
{
private:

	//链表节点
	struct name
	{
		Type data;
		struct name *next;
	};
	typedef name NODE;
	typedef NODE* PNODE;
	
	//链表元素个数
	int Linked_list_number;
	
	//头结点
	PNODE head;

	//尾节点
	PNODE rear;

public:

	//构造函数
	LINKLIST()
	{
		head = new NODE();
		head->next = NULL;
		rear = new NODE();
		rear->next = NULL;
		Linked_list_number = 0;
	}

	//析构函数
	virtual ~LINKLIST()
	{
		clear();
		delete(head);
		delete(rear);
	}

	//将元素添加到队尾
	void push(Type data)
	{
		if (empty())
		{
			rear->next = new NODE;
			head->next = rear->next;
		}
		else
		{
			rear->next->next = new NODE;
			rear->next = rear->next->next;
		}
		rear->next->data = data;
		rear->next->next = NULL;
		Linked_list_number++;
	}

	//将元素添加到队尾
	void push_back(Type data)
	{
		if (empty())
		{
			rear->next = new NODE;
			head->next = rear->next;
		}
		else
		{
			rear->next->next = new NODE;
			rear->next = rear->next->next;
		}
		rear->next->data = data;
		rear->next->next = NULL;
		Linked_list_number++;
	}

	//将元素添加到队头
	void push_front(Type data)
	{
		if (empty())
		{
			push(data);
		}
		else
		{
			PNODE addition = new NODE;
			addition->data = data;
			addition->next = head->next;
			head->next = addition;
			Linked_list_number++;
		}
	}

	//将元素添加到第n个元素后
	void push_num(Type data, int n)
	{
		if (n < 0 || n > Linked_list_number) return;
		if (n == 0)
		{
			push(data);
			return;
		}
		PNODE p = head;
		while (n > 1)
		{
			if (p == NULL) return;
			else p = p->next;
			n--;
		}
		PNODE addition = new NODE;
		p->next == rear->next && (rear->next = addition);
		addition->next = p->next;
		p->next = addition;
		Linked_list_number++;
	}

	//返回头元素
	Type front()
	{
		if (empty()) return Type();
		return head->next->data;
	}

	//返回尾元素
	Type back()
	{
		if (empty()) return Type();
		return rear->next->data;
	}

	//返回下标为n的元素
	Type visit(int n)
	{
		if (n < 0 || n >= Linked_list_number) return Type();
		PNODE p = head;
		while (n > 0)
		{
			p = p->next;
			n--;
		}
		return p->data;
	}

	//查找第一个相等元素的编号
	int find(Type data)
	{
		PNODE p = head;
		int num = 0;
		while (p->next)
		{
			p = p->next;
			num++;
			if (p->data == data) return num;
		}
		return -1;
	}

	//删除头元素
	void pop()
	{
		if (empty()) return;
		PNODE deletion = head->next;
		head->next = deletion->next;
		delete(deletion);
		Linked_list_number&&Linked_list_number--;
	}

	//删除第一个相等元素
	void pop_equal(Type data)
	{
		PNODE p = head;
		while (p->next)
		{
			if (p->next->data == data)
			{
				PNODE deletion = p->next;
				p->next = deletion->next;
				delete(deletion);
				Linked_list_number&&Linked_list_number--;
				return;
			}
			p = p->next;
		}
		return;
	}

	//删除从头开始的第n个元素
	void pop_num(int n)
	{
		if (empty()) return;
		if (n < 1 || n > Linked_list_number) return;
		PNODE p = head;
		while (n > 1)
		{
			if (p == NULL) return;
			else p = p->next;
			n--;
		}
		p->next == rear->next && (rear->next = p);
		PNODE deletion = p->next;
		p->next = deletion->next;
		delete(deletion);
		Linked_list_number&&Linked_list_number--;
	}

	//修改下标为n的元素
	void change(Type data, int n)
	{
		if (empty()) return;
		if (n < 0 || n >= Linked_list_number) return;
		PNODE p = head;
		while (n > 0)
		{
			p = p->next;
			n--;
		}
		p->next->data = data;
	}

	//清除所有元素
	void clear()
	{
		PNODE p = head;
		while (p->next != NULL)
		{
			PNODE deletion = p->next;
			p->next = deletion->next;
			delete(deletion);
		}
		rear->next = NULL;
		Linked_list_number = 0;
	}

	//返回队列元素个数
	int length()
	{
		return Linked_list_number;
	}

	//返回是否为空
	bool empty()
	{
		return Linked_list_number == 0;
	}

	//重载等号，进行深拷贝
	void operator = (LINKLIST &List)
	{
		clear();
		PNODE p = List.head;
		while (p->next != NULL)
		{
			p = p->next;
			push(p->data);
		}
	}

};

#endif // !_MY_LINKLIST
