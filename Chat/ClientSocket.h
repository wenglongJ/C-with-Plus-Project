#pragma once
#include "afxsock.h"
#include "Messg.h"
#include "ChatDlg.h"
class CChatDlg;
class CMessg;
class CClientSocket :
	public CSocket
{
public:
	CArchive *m_aSessionIn;
	CArchive *m_aSessionOut;
	CSocketFile *m_sfSocketFile;
	CChatDlg *m_dlg;
	bool m_bInit;
	bool m_bClose;

	void Init(CChatDlg *dlg);
	bool SendMessage(CMessg *msg);
	void CloseSocket();

	static int GetLocalHostName(CString &sHostName);
	static int GetIpAddress(CString &sHostName, CString &sIpAddress);
	static int GetIpAddress(CString &sHostName, BYTE &f0, BYTE &f1, BYTE &f2, BYTE &f3);
	static CString ErrorReason(int tag);

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	CClientSocket();
	~CClientSocket();
};

