#include "Header.h"
#include <iostream>
#include <string>
using namespace std;

void Target::request()
{
	cout << "普通请求！" << endl;
}

Target::~Target()
{
	cout << "Target::~Target() called!" << endl;
}

void Adaptee::specificRequest()
{
	cout << "特殊请求！" << endl;
}

void Adapter::request()
{
	adaptee->specificRequest();
}

Adapter::~Adapter()
{
	cout << "Adapter::~Adapter() called!" << endl;
}

Adapter::Adapter()
{
	//建立一个私有的Adaptee对象
	adaptee = new Adaptee;
}