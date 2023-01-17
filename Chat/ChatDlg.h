
// ChatDlg.h : header file
//

#pragma once
#include "ClientSocket.h"
#include "ServerSocket.h"

class CClientSocket;
class CServerSocket;
// CChatDlg dialog
class CChatDlg : public CDialogEx
{
// Construction
public:
	CChatDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	UINT m_uPort;
	CString m_sShowString;
	CString m_sInputText;
	CString m_sName;
	bool m_bInit;
	bool m_bClient;

	CClientSocket *m_clientsocket;
	CServerSocket *m_pListenSocket;
	CPtrList m_connectionList;
	CString m_sMsgList;

	void ProcessPendingAccept();
	void CloseSessionSocket();
	void ClearContent();
	void OnClearconnection();

	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedSetserver();
	afx_msg void OnBnClickedSend();
	afx_msg void OnEnChangeInputtext();
};
