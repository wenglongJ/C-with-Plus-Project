#include "stdafx.h"
#include "ClientSocket.h"
#include "Chat.h"
#include "ChatDlg.h"
#pragma warning(disable : 4996)

CClientSocket::CClientSocket()
{
	m_aSessionIn = NULL;
	m_aSessionOut = NULL;
	m_sfSocketFile = NULL;
	m_bInit = false;
	m_bClose = false;
}


CClientSocket::~CClientSocket()
{
	if (m_aSessionIn)
		delete m_aSessionIn;
	if (m_aSessionOut)
		delete m_aSessionOut;
	if (m_sfSocketFile)
		delete m_sfSocketFile;
}

void CClientSocket::Init(CChatDlg *dlg) {
	m_sfSocketFile = new CSocketFile(this);
	m_aSessionIn = new CArchive(m_sfSocketFile, CArchive::load);
	m_aSessionOut = new CArchive(m_sfSocketFile, CArchive::store);
	m_bClose = false;
	this->m_dlg = dlg;
}
bool CClientSocket::SendMessage(CMessg *msg) {
	if (m_aSessionOut != NULL) {
		msg->Serialize(*m_aSessionOut);
		m_aSessionOut->Flush();
		return true;
	}
	else {
		m_bClose = true;
		CloseSocket();
		m_dlg->CloseSessionSocket();
		return FALSE;
	}
}
void CClientSocket::CloseSocket() {
	if (m_aSessionIn) {
		delete m_aSessionIn;
		m_aSessionIn = NULL;
	}
	if (m_aSessionOut) {
		delete m_aSessionOut;
		m_aSessionOut = NULL;
	}
	if (m_sfSocketFile) {
		delete m_sfSocketFile;
		m_sfSocketFile = NULL;
	}
	Close();
	m_bInit = false;
	m_bClose = true;
}

int CClientSocket::GetLocalHostName(CString &sHostName) {
	char szHostName[256];
	int nRetCode;
	nRetCode = gethostname(szHostName, sizeof(szHostName));
	if (nRetCode != 0) {
		sHostName = _T("没有取得");
		return GetLastError();
	}
	sHostName = szHostName;
	return 0;
}
int  CClientSocket::GetIpAddress(CString &sHostName, CString &sIpAddress) {
	struct hostent FAR *lpHostEnt = gethostbyname(sHostName);
	if (lpHostEnt == NULL) {
		sIpAddress = _T("");
		return GetLastError();
	}
	LPSTR lpAddr = lpHostEnt->h_addr_list[0];
	if (lpAddr) {
		struct in_addr inAddr;
		memmove(&inAddr, lpAddr, 4);
		sIpAddress = inet_ntoa(inAddr);
		if (sIpAddress.IsEmpty()) {
			sIpAddress = _T("没有取得");
		}
	}
}
int  CClientSocket::GetIpAddress(CString &sHostName, BYTE &f0, BYTE &f1, BYTE &f2, BYTE &f3) {
	struct hostent FAR * lpHostEnt = gethostbyname(sHostName);
	if (lpHostEnt == NULL) {
		f0 = f1 = f2 = f3 = 0;
		return GetLastError();
	}
	LPSTR lpAddr = lpHostEnt->h_addr_list[0];
	if (lpAddr) {
		struct in_addr inAddr;
		memmove(&inAddr, lpAddr, 4);
		f0 = inAddr.S_un.S_un_b.s_b1;
		f1 = inAddr.S_un.S_un_b.s_b2;
		f2 = inAddr.S_un.S_un_b.s_b3;
		f3 = inAddr.S_un.S_un_b.s_b4;
	}
	return 0;
}
CString CClientSocket::ErrorReason(int tag) {
	CString result;
	switch (tag) {

	}
	return result;
}

void CClientSocket::OnReceive(int nErrorCode) {
	CSocket::OnReceive(nErrorCode);
	do {
		CMessg temp;
		temp.Serialize(*m_aSessionIn);
		m_dlg->m_sMsgList += temp.m_strText + _T("\r\n");
		m_dlg->SetDlgItemText(IDC_SHOWTEXT, m_dlg->m_sMsgList);
		int linenum = ((CEdit *)(m_dlg->GetDlgItem(IDC_SHOWTEXT)))->GetLineCount();
		((CEdit *)(m_dlg->GetDlgItem(IDC_SHOWTEXT)))->LineScroll(linenum);
		if (!m_dlg->m_bClient) {
			for (POSITION pos = m_dlg->m_connectionList.GetHeadPosition();
				pos != NULL;) {
				CClientSocket*t = (CClientSocket *)m_dlg->m_connectionList.GetNext(pos);
				if (t->m_hSocket != this->m_hSocket) {
					t->SendMessage(&temp);
				}
			}
		}
	} while (!m_aSessionIn->IsBufferEmpty());
}
void CClientSocket::OnClose(int nErrorCode) {
	m_bClose = true;
	CloseSocket();
	m_dlg->CloseSessionSocket();
	CSocket::OnClose(nErrorCode);
}
