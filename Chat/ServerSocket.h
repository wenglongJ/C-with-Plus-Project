#pragma once
#include "afxsock.h"
#include "ChatDlg.h"
#include "Chat.h"
class CChatDlg;
class CServerSocket :
	public CSocket
{
public:
	CServerSocket();
	~CServerSocket();

	CChatDlg *m_dlg;
	UINT m_uPort;
	bool Init(UINT port, CChatDlg *dlg);

	virtual void OnAccept(int nErrorCode);
};

