// 四则运算.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main(int argc , char ** argv)
{
	//提示参数效果
	if (argc != 3)
	{
		puts("Instruction:");
		puts("argv[1]: '-c' for creating questions. And argv[2] is the file path and name.");
		puts("argv[1]: '-test' for take a test. And argv[2] is the number you want to try.");
		return 0;
	}
	int cont_right = 0, i;
	char input[30] = { 0 };
	if (!strcmp(argv[1], "-c"))//creating questions
		CreateExpression C(argv[2]);
	else if (!strcmp(argv[1], "-test"))//solve
	{
		CreateExpression C("tmp.txt");
		Solve S;
		FILE *p = fopen("tmp.txt", "r");
		for (i = 0; i < atoi(argv[2]); i++)
		{
			printf("Question %d:\n", i + 1);
			char Question[70] = { 0 };
			fgets(Question, 70, p);
			Question[strlen(Question) - 1] = 0;
			printf("%s=\n", Question);
			Fraction Ans = S.solve(Question);
			int Start_Time = clock();
			scanf("%s",input);
			int isNegative = false;
			if (input[0] == '-')
			{
				isNegative = true;
				input[0] = ' ';
			}
			int End_Time = clock();
			Fraction ans = S.solve(input);
			if (isNegative)
			{
				ans = -ans;
			}
			if (ans == Ans)
			{
				cont_right++;
				puts("perfect!");
			}
			else
			{
				printf("Wrong!\n");
				printf("The correct answer is ");
				cout << Ans.String() << endl;
			}
			printf("You spend %d seconds to give the answer\n", (End_Time - Start_Time) / 1000);
		}
		printf("\nSummary:\n");
		printf("%d right and %d wrong\n", cont_right, i - cont_right);
		printf("Your correct rate is:%.2f%%\n", (double)cont_right * 100 / i);
	}
	return 0;
}
