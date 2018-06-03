#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stack>
#include "Fraction.h"
#include "CreateExpression.h"
#include "Expression.h"
//#include "Linklist.h"
//#include "ProbabilityBox.h"
//#include "Random.h"
using namespace std;

int main(int argc, char **argv)
{
	//提示参数效果
	//if (argc == 1)
	//{
	//	puts("Instruction:");
	//	puts("argv[1]: '-c' for creating questions. And argv[2] is the file path and name.");
	//	puts("argv[1]: '-test' for take a test. And argv[2] is the number you want to try.");
	//	return 0;
	//}
	int cont_right=0, i;
	char ans[30] = { 0 };
	//Expression xxx;
	//if (!strcmp(argv[1], "-c"))//creating questions
	if(1)
	{
		CreateExpression xxx;
		//FILE *p = fopen(argv[2], "w");
		for (i = 0; i < 1000; i++)
		{
			xxx.Create();
			xxx.Print();
			//fwrite(xxx.exp, 30, 1, p);
		}
		//fclose(p);
	}
	else if (!strcmp(argv[1], "-test"))//solve
	{
		for (i = 0; i < atoi(argv[2]); i++)
		{
			//xxx.creat_exp();
			//printf("%s = ", xxx.exp);

		}
		printf("%d right and %d wrong\n", cont_right, i - cont_right);
		printf("Your correct rate is:%.2f%%\n", (double)cont_right * 100 / i);

	}
}