#include "my.h"//ԭ������mfc.h�ͺã���Ϊ��CMyWinApp�Ķ��壬����...
extern CMyWinApp theApp;
CWinApp* AfxGetApp()
{
    return theApp.m_pCurrentWinApp;
}