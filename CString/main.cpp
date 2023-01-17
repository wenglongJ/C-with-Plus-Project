#include "CString.h"
#include <stdio.h>

int main()
{
	CString cstr1("hello world");

	CString cstr2(cstr1);

	cstr1 = cstr1;

	CString cstr3 = cstr1;

	CString cstr4;

	char *pSrc = NULL;
	CString cstr5(pSrc);

	getchar();
	return 0;
}