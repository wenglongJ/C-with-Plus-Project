#pragma once
#include "afx.h"
#include "ChatDlg.h"
class CMessg :
	public CObject
{
protected:
	DECLARE_DYNCREATE(CMessg)
public:
	CMessg();
	~CMessg();

	CString m_strText;
	void Init();
	virtual void Serialize(CArchive &ar);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext &dc)const;
#endif
};

