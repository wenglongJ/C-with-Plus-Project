#include<iostream>
#include<assert.h>
#include"Factorial.h"

using namespace std;

int Factorial(int n) 
{
	if (n > 1 && n < 13)
	{
		return n*Factorial(n - 1);
	}
	else if (n >= 13)
	{
		//throw "是一个极大的正整数，阶乘超过int范围越界！请输入一个有效的正整数";
		return 0;
	}
	else if(n == 1 || n == 0)
	{
		return 1;
	}
	else  	//n为一个负数
	{
		//throw "是一个负数，没有阶乘！请输入一个有效的正整数";
		return 0;
	}
}

void TestFactorial()
{
	//正整数临界值 13、12,正常值5 2 1的阶乘
	assert(Factorial(12) == 479001600);

	//assert(Factorial(13) == 6227020800);
	assert(Factorial(13) == 0);

	assert(Factorial(5) == 120);

	assert(Factorial(1) == 1);

	assert(Factorial(2) == 2);

	//特殊数字0的阶乘 应该为1
	assert(Factorial(0) == 1);

	//负数的阶乘 应该报错 -5
	assert(Factorial(-5) == 0);

	//浮点数5.2 应该无阶乘
	//系统警告但是有结果
	assert(Factorial(5.2) == 120);

	//对于极大的正整数>=13 对于极大数会产生越界
	assert(Factorial(100) == 0);
}