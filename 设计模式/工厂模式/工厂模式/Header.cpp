#include "Header.h"
#include <iostream>
#include <string>
using namespace std;

Operation *IFactory::createOperation()
{
	return nullptr;
}

Operation *AddFactory::createOperation()
{
	return new AddOperation;
}

double Operation::getResult()
{
	return -1;
}

AddOperation::AddOperation()
{
	m_numberA = 0.0;
	m_numberB = 0.0;
}

double AddOperation::getResult()
{
	return m_numberA + m_numberB;
}

MultiOperation::MultiOperation()
{
	m_numberA = 0.0;
	m_numberB = 0.0;
}

double MultiOperation::getResult()
{
	return m_numberA * m_numberB;
}

Operation * MultiFactory::createOperation()
{
	return new MultiOperation;
}