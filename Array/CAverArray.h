#pragma once

#include "CMyArray.h"

class CAverArray : virtual public CMyArray
{
public:
	CAverArray(int nLen);

	double Average();
};