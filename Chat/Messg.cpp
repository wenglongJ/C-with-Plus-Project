#include "stdafx.h"
#include "Messg.h"

IMPLEMENT_DYNCREATE(CMessg, CObject);
CMessg::CMessg()
{
	Init();
}


CMessg::~CMessg()
{
}

void CMessg::Init() {
	m_strText = _T("");
}
void CMessg::Serialize(CArchive &ar) {
	if (ar.IsStoring()) {
		ar << m_strText;
	}
	else {
		ar >> m_strText;
	}
}
#ifdef _DEBUG
void CMessg::AssertValid() const {
	CObject::AssertValid();
}
void CMessg::Dump(CDumpContext &dc)const {
	CObject::Dump(dc);
}
#endif
