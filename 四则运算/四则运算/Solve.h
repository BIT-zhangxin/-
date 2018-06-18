#pragma once
#ifndef _MY_SOLVE
#define _MY_SOLVE

#include <string.h>
#include <cstring>
#include <stack>
#include "Fraction.h"

class Solve
{
private:
	
	char Expression[70] = { 0 };//原表达式
	char Postfix_Expression[70] = { 0 };//后缀表达式
	
private:

	//判断是否为合法字符
	bool isValid(char Sign)
	{
		if (Sign >= '0'&&Sign <= '9')
			return true;
		else if (Sign == '+' || Sign == '-' || Sign == '*' || Sign == '/' || Sign == '^')
			return true;
		else
			return false;
	}

	//符号优先级
	int Priority(char Sign)
	{
		switch (Sign)
		{
		case '#':
			return -1;
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;//优先级这里有点晕了。。歆歆看到的话检查一下
		default:
			return -1;
		}
	}

	//去掉空格和**，并在尾部加上#
	void Initialize()
	{
		int len = strlen(Expression);
		int now_loc = 0;
		for (int i = 0; i < len; i++)
		{
			if (i < len - 1 && Expression[i] == '*'&&Expression[i + 1] == '*')
			{
				Expression[now_loc++] = '^';
				i++;
			}
			else if (isValid(Expression[i]))
			{
				Expression[now_loc++] = Expression[i];
			}
		}
		Expression[now_loc++] = '#';
		Expression[now_loc] = 0;
	}

	//转成后缀表达式
	void Change_to_Postfix()
	{
		memset(Postfix_Expression, 0, sizeof(Postfix_Expression));
		int i = 0, j = 0;
		stack<char> Ooperator;
		Ooperator.push('#');
		while (Expression[i] != '#')
		{
			if ((Expression[i] >= '0' && Expression[i] <= '9'))
			{
				Postfix_Expression[j++] = Expression[i];
			}
			else if (Expression[i] == '(')//直接入栈
				Ooperator.push('(');
			else if (Expression[i] == ')')//将栈中对应其左括号后的操作符写入后缀表达式
			{
				while (Ooperator.top() != '(')
				{
					Postfix_Expression[j++] = Ooperator.top();
					Ooperator.pop();
				}
				Ooperator.pop();// pop (
			}
			else if (Expression[i] == '+' || Expression[i] == '-' || Expression[i] == '*' || Expression[i] == '/' || Expression[i] == '^')
			{
				Postfix_Expression[j++] = ' ';
				while (Priority(Expression[i]) <= Priority(Ooperator.top()))
				{
					Postfix_Expression[j++] = Ooperator.top();
					Ooperator.pop();
				}
				Ooperator.push(Expression[i]);
			}
			i++;
		}
		while (!Ooperator.empty())//最后所有操作符连入后缀表达式
		{
			Postfix_Expression[j++] = Ooperator.top();
			Ooperator.pop();
		}
	}

	//读取数字
	Fraction Readnum(int &i)
	{
		int  x = 0;
		while (Postfix_Expression[i] >= '0'&&Postfix_Expression[i] <= '9')
		{
			x = x * 10 + Postfix_Expression[i] - '0';
			i++;
		}
		Fraction val(x);
		return val;
	}

	//计算
	Fraction Calculate()
	{
		stack<Fraction> num_stack;//操作数栈
		int i = 0;
		Fraction x1, x2;
		while (Postfix_Expression[i] != '#')
		{
			if (Postfix_Expression[i] >= '0' && Postfix_Expression[i] <= '9')
				num_stack.push(Readnum(i));
			else if (Postfix_Expression[i] == ' ')
				i++;
			else if (Postfix_Expression[i] == '+')
			{
				x1 = num_stack.top();
				num_stack.pop();
				x2 = num_stack.top();
				num_stack.pop();
				num_stack.push(x1 + x2);//利用了对分数运算的符号重载
				i++;
			}
			else if (Postfix_Expression[i] == '-')
			{
				x1 = num_stack.top();
				num_stack.pop();
				x2 = num_stack.top();
				num_stack.pop();
				num_stack.push(x2 - x1);//利用了对分数运算的符号重载
				i++;
			}
			else if (Postfix_Expression[i] == '*')
			{
				x1 = num_stack.top();
				num_stack.pop();
				x2 = num_stack.top();
				num_stack.pop();
				num_stack.push(x1 * x2);//利用了对分数运算的符号重载
				i++;
			}
			else if (Postfix_Expression[i] == '/')
			{
				x1 = num_stack.top();
				num_stack.pop();
				x2 = num_stack.top();
				num_stack.pop();
				num_stack.push(x2 / x1);//利用了对分数运算的符号重载
				i++;
			}
			else if (Postfix_Expression[i] == '^')
			{
				x1 = num_stack.top();
				num_stack.pop();
				x2 = num_stack.top();
				num_stack.pop();
				num_stack.push(x2 ^ x1.Numerator);//利用了对分数运算的符号重载
				i++;
			}
		}
		return num_stack.top();
	}

public:
	
	Solve() = default;
	
public:

	Fraction solve(const char *Expression)
	{
		strcpy(this->Expression, Expression);
		Initialize();
		Change_to_Postfix();
		return Calculate();
	}

	Fraction solve(string Expression)
	{
		strcpy_s(this->Expression, Expression.c_str());
		Initialize();
		Change_to_Postfix();
		return Calculate();
	}

};

#endif // !_MY_SOLVE