#include "my.h"//原本含入mfc.h就好，但为了CMyWinApp的定义，所以...
extern CMyWinApp theApp;
CWinApp* AfxGetApp()
{
    return theApp.m_pCurrentWinApp;
}