#include "Header.h"
#include <iostream>
#include <afxmt.h>

CNameManager *CNameManager::m_pCNameManager = NULL;
std::mutex CNameManager::m_mutex;

CNameManager* CNameManager::SingleTon()
{
	if (m_pCNameManager == NULL)
	{
		Lock();
		if (m_pCNameManager == NULL)
		{

			m_pCNameManager = new CNameManager;
			Unlock();
			return m_pCNameManager;
		}
	}
	Unlock();
	return m_pCNameManager;
}

void CNameManager::Print()
{
	std::cout << "hello NameManage";
}

CNameManager::CNameManager()
{
}
CNameManager::~CNameManager()
{
}

int main()
{
	CNameManager::SingleTon()->Print();
	getchar();
	return 0;
}