// 3.3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMyArray.h"
#include "CSortArray.h"
#include "CReArray.h"
#include "CAverArray.h"
#include "CNewArray.h"
#include <iostream>

using namespace std;

void TestCMyArray();
void TestCSortArray();
void TestCReArray();
void TestCAverArray();
void TestCNewArray();

int main()
{
	//TestCMyArray();
	//TestCSortArray();
	//TestCReArray();
	//TestCAverArray();
	TestCNewArray();
	return 0;
}

void TestCMyArray()
{
	CMyArray myArray(-5);
	myArray.Display();

	CMyArray myArrays(10);
	myArrays.Input();
	myArrays.Display();
}

void TestCSortArray()
{
	CSortArray mySortArray(10);
	mySortArray.Input();
	mySortArray.Display();
	mySortArray.Sort();
	cout << "排序后：";
	mySortArray.Display();
}

void TestCReArray()
{
	CReArray myReArray(10);
	myReArray.Input();
	myReArray.Display();
	myReArray.Reserve();
	cout << "逆转后：";
	myReArray.Display();
}

void TestCAverArray()
{
	CAverArray myAverArray(10);
	myAverArray.Input();
	myAverArray.Display();
	double nAverage = myAverArray.Average();
	cout << "平均数：" << nAverage << endl;
}

void TestCNewArray()
{
	CNewArray myNewArrayEmpty(-5);
	myNewArrayEmpty.Display();

	CNewArray myNewArray(10);
	myNewArray.Input();
	myNewArray.Display();

	CSortArray *mySortArray = &myNewArray;
	mySortArray->Sort();
	cout << "排序后：";
	mySortArray->Display();

	CReArray *myReArray = &myNewArray;
	myReArray->Reserve();
	cout << "逆转后：";
	myReArray->Display();

	CAverArray *myAverArray = &myNewArray;
	double nAverage = myAverArray->Average();
	cout << "平均数：" << nAverage << endl;
}
