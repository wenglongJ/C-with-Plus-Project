#pragma once

class CMyArray
{
public:
	CMyArray(int nLen);
	~CMyArray();
	void Input();
	void Display();

protected:
	int *m_pBuf;
	int m_nLength;
};