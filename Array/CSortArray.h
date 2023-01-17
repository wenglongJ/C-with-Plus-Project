#pragma once
#include "CMyArray.h"

class CSortArray : virtual public CMyArray
{
public:
	CSortArray(int nLen);

	void Sort();
};