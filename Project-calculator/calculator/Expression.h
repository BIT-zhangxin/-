#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stack>
#include "Fraction.h"
#include "CreateExpression.h"
class Expression
{
public:
	void creat_exp()
	{
		memset(exp, 0, sizeof(exp));
		//从CreatExpression.h中将生成的string类型的式子转化成char*

	}
	void cut_space();//去掉空格和**
	void postfix();//转成后缀表达式
	int priority(char op);//符号优先级
	Fraction calculate();//计算
	Fraction readnum(int *i);//读取数字
	bool Check_ans(char Ans[30]);//检查答案
	char exp[50], post_exp[50];//原表达式和后缀表达式
	Fraction value;
};
//去掉表达式中的空格，将'**'转为'^'
void Expression::cut_space()
{
	for (int i = 0; i < strlen(exp); i++)
	{
		if (exp[i] == ' ')
			for (int j = i; j < strlen(exp); j++)
				exp[j] = exp[j + 1];
		else if (exp[i] = '*' && exp[i + 1] == '*')
		{
			exp[i] = '^';
			for (int j = i + 1; j < strlen(exp); j++)
				exp[j] = exp[j + 1];
		}
	}
	strcat(exp, "#"); 
}
//得到符号优先级。
int Expression::priority(char op)
{
	switch (op)
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
//中缀达式转成后缀表达式
void Expression::postfix()
{
	memset(post_exp, 0, sizeof(post_exp));
	int i = 0, j = 0;
	stack<char> Ooperator;
	Ooperator.push('#');
	while (exp[i] != '#')
	{
		if ((exp[i] >= '0' && exp[i] <= '9'))
		{
			post_exp[j++] = exp[i];
		}
		else if (exp[i] == '(')//直接入栈
			Ooperator.push('(');
		else if (exp[i] == ')')//将栈中对应其左括号后的操作符写入后缀表达式
		{
			while (Ooperator.top() != '(')
			{
				post_exp[j++] = Ooperator.top();
				Ooperator.pop();
			}
			Ooperator.pop();// pop (
		}
		else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^')
		{
			post_exp[j++] = ' ';
			while (priority(exp[i]) <= priority(Ooperator.top()))
			{
				post_exp[j++] = Ooperator.top();
				Ooperator.pop();
			}
			Ooperator.push(exp[i]);
		}
		i++;
	}
	while (!Ooperator.empty())//最后所有操作符连入后缀表达式
	{
		post_exp[j++] = Ooperator.top();
		Ooperator.pop();
	}
}
//从表达式中读取数；
Fraction Expression::readnum(int *i)
{
	int  x = 0;
	while (post_exp[*i] >= '0'&&post_exp[*i] <= '9')
	{
		x = x * 10 + post_exp[*i] - '0';
		(*i)++;
	}
	Fraction val(x);
	return val;
}
// 计算表达式的值（全部转成分数进行运算）
Fraction Expression::calculate()
{
	stack<Fraction> num_stack;//操作数栈
	int i = 0;
	Fraction x1, x2;
	while (post_exp[i] != '#')
	{
		if (post_exp[i] >= '0' && post_exp[i] <= '9')
			num_stack.push(readnum(&i));
		else if (post_exp[i] == ' ')
			i++;
		else if (post_exp[i] == '+')
		{
			x1 = num_stack.top();
			num_stack.pop();
			x2 = num_stack.top();
			num_stack.pop();
			num_stack.push(x1 + x2);//利用了对分数运算的符号重载
		}
		else if (post_exp[i] == '-')
		{
			x1 = num_stack.top();
			num_stack.pop();
			x2 = num_stack.top();
			num_stack.pop();
			num_stack.push(x1 - x2);//利用了对分数运算的符号重载
		}
		else if (post_exp[i] == '*')
		{
			x1 = num_stack.top();
			num_stack.pop();
			x2 = num_stack.top();
			num_stack.pop();
			num_stack.push(x1 * x2);//利用了对分数运算的符号重载
		}
		else if (post_exp[i] == '/')
		{
			x1 = num_stack.top();
			num_stack.pop();
			x2 = num_stack.top();
			num_stack.pop();
			num_stack.push(x1 / x2);//利用了对分数运算的符号重载
		}
		else if (post_exp[i] == '^')
		{
			if (x2.isInteger())
				x1 = num_stack.top();
			num_stack.pop();
			x2 = num_stack.top();
			num_stack.pop();
			num_stack.push(x1 ^ x2.Integer());//利用了对分数运算的符号重载
		}
	}
	return num_stack.top();
}
//检查答案是否正确
bool Expression::Check_ans(char Ans[30])
{
	bool fra = 0;//表示结果是整数，1则为分数
	for (int i = 0; i < strlen(Ans); i++)
	{
		if (Ans[i] == '/')
		{
			fra = 1;
			break;
		}
	}
	if (!fra)
	{
		if (value.isInteger&&value.Integer() == atoi(Ans))
			return true;
		else
			return false;
	}
	else
	{
		Expression answer;
		strcpy(answer.exp, Ans);
		answer.cut_space();
		answer.postfix();
		answer.value = answer.calculate();
		if (answer.value.Double() == value.Double())
			return true;
		else
			return false;
	}
}