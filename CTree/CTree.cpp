#include "CTree.h"
#include "windows.h"

void CTree::SelectAll()
{
	this->GetRootItem()->SetItemState(1);
}

void CTree::DeselectAll()
{
	this->GetRootItem()->SetItemState(0);
}

void CTree::InvertSelection()
{
	SetReserveState(*this->GetRootItem());
}

void CTree::SetReserveState(CTreeItem &treeItem)
{
	int nState = treeItem.GetItemState();
	if (nState == 0)
	{
		treeItem.SetItemState(1);
	}
	else if (nState == 1)
	{
		treeItem.SetItemState(0);
	}
	else   //nState==2
	{
		//��������
		CTreeItem *pCTreeChildItem = treeItem.GetChildItem();
		if (pCTreeChildItem != NULL)
		{
			SetReserveState(*pCTreeChildItem);

			//���������ֵ�
			CTreeItem *pCTreeNextItem = pCTreeChildItem->GetNextItem();
			while (pCTreeNextItem != NULL)
			{
				SetReserveState(*pCTreeNextItem);
				pCTreeNextItem = pCTreeNextItem->GetNextItem();
			}
		}
	}
}


//stack<CTreeItem *> stackCTree;
//stackCTree.push(this->m_pCTreeItem);

////ѭ�������ӽڵ�
//while (!stackCTree.empty())
//{
//	CTreeItem *pCTreeChildItem = stackCTree.top();
//	stackCTree.pop();

//	//���ýڵ�״̬
//	pCTreeChildItem->SetItemState(1);

//	pCTreeChildItem = pCTreeChildItem->GetChildItem();
//	//�ѽڵ㺢��ѹջ
//	if (pCTreeChildItem != NULL)
//	{
//		stackCTree.push(pCTreeChildItem->GetChildItem());
//	}

//	//�ѽڵ��ֵܽڵ�ѹջ
//	CTreeItem *pCTreeNextItem = pCTreeChildItem->GetNextItem();
//	while (pCTreeNextItem != NULL)
//	{
//		stackCTree.push(pCTreeNextItem);
//		pCTreeNextItem = pCTreeNextItem->GetNextItem();
//	}
//}

