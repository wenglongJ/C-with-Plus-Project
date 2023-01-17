#include "stdafx.h"
#include "ServerSocket.h"


CServerSocket::CServerSocket()
{
}


CServerSocket::~CServerSocket()
{
}

bool CServerSocket::Init(UINT port, CChatDlg *dlg) {
	m_uPort = port;
	m_dlg = dlg;
	if (Create(m_uPort) == FALSE) {
		AfxMessageBox(_T("Server Socket Create Error"));
		return FALSE;
	}
	if (this->Listen() == FALSE) {
		AfxMessageBox(_T("Server Listen Error"));
		return FALSE;
	}
	m_dlg->SetDlgItemText(IDC_SHOWTEXT, _T("Server Has Been Set OK!"));
	return TRUE;
}

void CServerSocket::OnAccept(int nErrorCode) {
	m_dlg->ProcessPendingAccept();
	CSocket::OnAccept(nErrorCode);
}
