#include <stdio.h>

int AnswerN = 0;//作为标志，默认为0，无解保持原值，输出无解；有解变成1，输出结果
char equation2[10];
char equation1[10];
void count2(int a, int b)//作为上级，由从中级得到的两个数通过加减乘除判断是否满足条件，满足则输出满足结果的等式组
{
	//两数相加等于24的情况
	if (a + b == 24)
	{
		AnswerN++;
		printf("%s\t%s\t%d+%d=24\n", equation1, equation2, a, b);
	}
	//两数相乘等于24的情况
	if (a * b == 24)
	{
		AnswerN++;
		printf("%s\t%s\t%d*%d=24\n", equation1, equation2, a, b);
	}
	//两数相减等于24的情况
	if (a - b == 24)
	{
		AnswerN++;
		printf("%s\t%s\t%d-%d=24\n", equation1, equation2, a, b);
	}
	if (b - a == 24)
	{
		AnswerN++;
		printf("%s\t%s\t%d-%d=24\n", equation1, equation2, b, a);
	}
	//两数相除等于24的情况
	if ((b != 0) && (a == 24 * b))
	{
		AnswerN++;
		printf("%s\t%s\t%d/%d=24\n", equation1, equation2, a, b);
	}
	if ((a != 0) && (b == 24 * a))
	{
		AnswerN++;
		printf("%s\t%s\t%d/%d=24\n", equation1, equation2, b, a);
	}
}
void count3(int a, int b, int c)
//作为中级，由从下级得到三个数，用两个通过加减乘除得到一个新数与一个等式，并将另一个数，新数与等式输出给上级
{
	int value[3];
	int i, j, k, newvalue;
	value[0] = a;
	value[1] = b;
	value[2] = c;
	for (i = 0; i < 3; i++)
	{
		for (j = i + 1; j < 3; j++)
		{
			k = 3 - i - j;//输出给上级的数
			//两数相加得新数
			newvalue = value[i] + value[j];
			sprintf_s(equation2, "%d+%d=%d", value[i], value[j], newvalue);//得到一个等式输给上级
			count2(newvalue, value[k]);//将新数和另一个数输出给上级
			//两数相乘得新数
			newvalue = value[i] * value[j];
			sprintf_s(equation2, "%d*%d=%d", value[i], value[j], newvalue);
			count2(newvalue, value[k]);
			//两数相减得新数
			if (value[i] > value[j])
			{
				newvalue = value[i] - value[j];
				sprintf_s(equation2, "%d-%d=%d", value[i], value[j], newvalue);
				count2(newvalue, value[k]);
			}
			else
			{
				newvalue = value[j] - value[i];
				sprintf_s(equation2, "%d-%d=%d", value[j], value[i], newvalue);
				count2(newvalue, value[k]);
			}
			//两数相除得新数
			if ((value[j] != 0) && (value[i] % value[j] == 0))
			{
				newvalue = value[i] / value[j];
				sprintf_s(equation2, "%d/%d=%d", value[i], value[j], newvalue);
				count2(newvalue, value[k]);
			}
			else if ((value[i] != 0) && (value[j] % value[i] == 0))
			{
				newvalue = value[j] / value[i];
				sprintf_s(equation2, "%d/%d=%d", value[j], value[i], newvalue);
				count2(newvalue, value[k]);
			}
		}
	}
}
void count4(int a, int b, int c, int d)
//作为下级，由输入的四个数，用两个通过加减乘除得到一个新数与一个等式，并将另两个数，新数输出给中级，等式输出给上级
{
	int value[4];
	int i, j, k, m, newvalue;
	value[0] = a;
	value[1] = b;
	value[2] = c;
	value[3] = d;
	for (i = 0; i < 4; i++)
	{
		for (j = i + 1; j < 4; j++)
		{
			for (k = 0; (k == i) || (k == j); k++);//输出给中级的数
			m = 6 - i - j - k;//输出给中级的数
			//两数相加得新数
			newvalue = value[i] + value[j];
			sprintf_s(equation1, "%d+%d=%d", value[i], value[j], newvalue);//得到一个等式输给上级
			count3(newvalue, value[k], value[m]);//将新数和另两个数输出给中级
			//两数相乘得新数
			newvalue = value[i] * value[j];
			sprintf_s(equation1, "%d*%d=%d", value[i], value[j], newvalue);
			count3(newvalue, value[k], value[m]);
			//两数相减得新数
			if (value[i] > value[j])
			{
				newvalue = value[i] - value[j];
				sprintf_s(equation1, "%d-%d=%d", value[i], value[j], newvalue);
				count3(newvalue, value[k], value[m]);
			}
			else
			{
				newvalue = value[j] - value[i];
				sprintf_s(equation1, "%d-%d=%d", value[j], value[i], newvalue);
				count3(newvalue, value[k], value[m]);
			}
			//两数相除得新数
			if ((value[j] != 0) && (value[i] % value[j] == 0))
			{
				newvalue = value[i] / value[j];
				sprintf_s(equation1, "%d/%d=%d", value[i], value[j], newvalue);
				count3(newvalue, value[k], value[m]);
			}
			else if ((value[i] != 0) && (value[j] % value[i] == 0))
			{
				newvalue = value[j] / value[i];
				sprintf_s(equation1, "%d/%d=%d", value[j], value[i], newvalue);
				count3(newvalue, value[k], value[m]);
			}
		}
	}
}
int main()
{
	do
	{
		int a, b, c, d;
		printf("输入4个数:");
		scanf_s("%d%d%d%d", &a, &b, &c, &d);
		count4(a, b, c, d);
		if (AnswerN == 0)
			printf("无解\n");
		printf("结束\n");
	} while (1);
	return 0;
}
