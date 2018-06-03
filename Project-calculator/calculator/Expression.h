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
		//��CreatExpression.h�н����ɵ�string���͵�ʽ��ת����char*

	}
	void cut_space();//ȥ���ո��**
	void postfix();//ת�ɺ�׺���ʽ
	int priority(char op);//�������ȼ�
	Fraction calculate();//����
	Fraction readnum(int *i);//��ȡ����
	bool Check_ans(char Ans[30]);//����
	char exp[50], post_exp[50];//ԭ���ʽ�ͺ�׺���ʽ
	Fraction value;
};
//ȥ�����ʽ�еĿո񣬽�'**'תΪ'^'
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
//�õ��������ȼ���
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
		return 3;//���ȼ������е����ˡ����짿����Ļ����һ��
	default:
		return -1;
	}
}
//��׺��ʽת�ɺ�׺���ʽ
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
		else if (exp[i] == '(')//ֱ����ջ
			Ooperator.push('(');
		else if (exp[i] == ')')//��ջ�ж�Ӧ�������ź�Ĳ�����д���׺���ʽ
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
	while (!Ooperator.empty())//������в����������׺���ʽ
	{
		post_exp[j++] = Ooperator.top();
		Ooperator.pop();
	}
}
//�ӱ��ʽ�ж�ȡ����
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
// ������ʽ��ֵ��ȫ��ת�ɷ����������㣩
Fraction Expression::calculate()
{
	stack<Fraction> num_stack;//������ջ
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
			num_stack.push(x1 + x2);//�����˶Է�������ķ�������
		}
		else if (post_exp[i] == '-')
		{
			x1 = num_stack.top();
			num_stack.pop();
			x2 = num_stack.top();
			num_stack.pop();
			num_stack.push(x1 - x2);//�����˶Է�������ķ�������
		}
		else if (post_exp[i] == '*')
		{
			x1 = num_stack.top();
			num_stack.pop();
			x2 = num_stack.top();
			num_stack.pop();
			num_stack.push(x1 * x2);//�����˶Է�������ķ�������
		}
		else if (post_exp[i] == '/')
		{
			x1 = num_stack.top();
			num_stack.pop();
			x2 = num_stack.top();
			num_stack.pop();
			num_stack.push(x1 / x2);//�����˶Է�������ķ�������
		}
		else if (post_exp[i] == '^')
		{
			if (x2.isInteger())
				x1 = num_stack.top();
			num_stack.pop();
			x2 = num_stack.top();
			num_stack.pop();
			num_stack.push(x1 ^ x2.Integer());//�����˶Է�������ķ�������
		}
	}
	return num_stack.top();
}
//�����Ƿ���ȷ
bool Expression::Check_ans(char Ans[30])
{
	bool fra = 0;//��ʾ�����������1��Ϊ����
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