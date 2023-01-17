#pragma once

#include "CMyArray.h"

class CReArray : virtual public CMyArray
{
public:
	CReArray(int nLen);

	void Reserve();
};