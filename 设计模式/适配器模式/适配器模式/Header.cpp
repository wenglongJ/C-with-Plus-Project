#include "Header.h"
#include <iostream>
#include <string>
using namespace std;

void Target::request()
{
	cout << "��ͨ����" << endl;
}

Target::~Target()
{
	cout << "Target::~Target() called!" << endl;
}

void Adaptee::specificRequest()
{
	cout << "��������" << endl;
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
	//����һ��˽�е�Adaptee����
	adaptee = new Adaptee;
}