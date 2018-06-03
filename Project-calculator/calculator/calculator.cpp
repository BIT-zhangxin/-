int main(int argc, char **argv)
{
	if (argc == 1)
	{
		puts("Instruction:");
		puts("argv[1]: '-c' for creating questions. And argv[2] is the file path and name.");
		puts("argv[1]: '-test' for take a test. And argv[2] is the number you want to try.");
	}
	int cont_right, i;
	char ans[15] = { 0 };
	Expression xxx;
	if (!strcmp(argv[1], "-c"))//creating questions
	{
		FILE *p = fopen(argv[2], "w");
		for (i = 0; i < 1000; i++)
		{
			xxx.creat_exp();
			fwrite(xxx.exp, 30, 1, p);
		}
		fclose(p);
	}
	else if (!strcmp(argv[1], "-test"))//solve
	{
		for (i = 0; i < atoi(argv[2]); i++)
		{
			xxx.creat_exp();
			printf("%s = ", xxx.exp);

		}
		printf("%d right and %d wrong\n", cont_right, i - cont_right);
		printf("Your correct rate is:%.2f%%\n", (double)cont_right * 100 / i);

	}
}