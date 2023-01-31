#include "Header.h"
#include <iostream>
#include <string>
using namespace std;

int main(int *argc, int *argv[]) {

	Target *target = new Adapter;
	target->request();
	delete target;

	getchar();
	return 0;
}