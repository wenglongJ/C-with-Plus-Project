#pragma once
#include "CAverArray.h"
#include "CReArray.h"
#include "CSortArray.h"
#include "CMyArray.h"

class CNewArray : virtual public CReArray, virtual public CAverArray, virtual public CSortArray
{
public:
	CNewArray(int nLen);
};