#include "Header.h"
#include <iostream>
using namespace std;

int main(int *argc, int *argv) {

	IFactory *operAddFactory = new AddFactory;
	Operation *addOper = operAddFactory->createOperation();
	addOper->m_numberA = 100;
	addOper->m_numberB = 200;
	cout << "operAddFactory result is : " << addOper->getResult() << endl;
	delete operAddFactory;
	delete addOper;

	cout << "--------------- 华丽的分割线 ---------------" << endl;
	IFactory *operMultiFactory = new MultiFactory;
	Operation *multiOper = operMultiFactory->createOperation();
	multiOper->m_numberA = 12;
	multiOper->m_numberB = 5;
	cout << "operMultiFactory result is : " << multiOper->getResult() << endl;
	delete operMultiFactory;
	delete multiOper;

	getchar();
	return 0;
}