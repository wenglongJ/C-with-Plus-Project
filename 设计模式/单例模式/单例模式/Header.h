#pragma once
#include <mutex>

class CNameManager
{
public:
	static CNameManager* SingleTon();
	static void Print();

	static void Lock()
	{
		m_mutex.lock();
	}

	static void Unlock()
	{
		m_mutex.unlock();
	}


private:
	CNameManager();
	~CNameManager();

private:
	static std::mutex m_mutex;

	static CNameManager *m_pCNameManager;
};

