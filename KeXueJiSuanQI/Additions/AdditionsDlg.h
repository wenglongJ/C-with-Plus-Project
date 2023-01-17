
// AdditionsDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "AnhuiDlg.h"
#include "KexueDlg.h"

#define POINT_COUNT 100


// CAdditionsDlg 对话框
class CAdditionsDlg : public CDialogEx
{
// 构造
public:
	CAdditionsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDITIONS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInstructButton();
	afx_msg void OnBnClickedOpenButton();
	afx_msg void OnBnClickedSaveButton();
private:
	CFont m_font;
public:
	afx_msg void OnBnClickedFontButton();
	afx_msg void OnBnClickedColorButton();
	CButton m_com;
	CButton m_sofware;
	CButton m_english;
	CButton m_japanese;
	CButton m_civil;
	CButton m_cost;
	int choose;
	void AllCheck();
	afx_msg void OnBnClickedComRadio();
	afx_msg void OnBnClickedBuiRadio();
	afx_msg void OnBnClickedLanRadio();
	afx_msg void OnBnClickedSureButton();
	afx_msg void OnLbnSelchangeWebList();
	CListBox m_list;
	CComboBox m_combox;
	afx_msg void OnCbnSelchangeWebCombo();
	CEdit m_horiScrollbar;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CScrollBar m_horiScrollbars;
	CListCtrl m_jiaodaList;
	afx_msg void OnLvnItemchangedJiaodaList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedWebTree(NMHDR *pNMHDR, LRESULT *pResult);
	CTreeCtrl m_tree;
	CImageList m_imageList;
	CTabCtrl m_tab;
	CAnhuiDlg anhuitu;
	CKexueDlg kexuetu;
	afx_msg void OnTcnSelchangeTabSee(NMHDR *pNMHDR, LRESULT *pResult);
	int m_nData1;
	int m_nData2;
	int m_nData3;
	afx_msg void OnBnClickedButtonTabsure();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_nTextX;
	int m_nTextY;
	CFont m_newFont;
	CFont *m_pOldFont;
	CStatic m_picDraw;
	int m_nzValues[POINT_COUNT];
	void DrawWave(CDC *pDC, CRect &rectPicture);
	afx_msg void OnDestroy();
	CStatic m_picColor;
	CComboBox m_somboy;
	double m_datafirst;
	double m_datasecond;
	double m_dataresult;
	afx_msg void OnBnClickedButtonCount();
	afx_msg void OnBnClickedButtonNew();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CProgressCtrl m_set;
	virtual void OnOK();
};
