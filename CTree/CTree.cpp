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
		//遍历孩子
		CTreeItem *pCTreeChildItem = treeItem.GetChildItem();
		if (pCTreeChildItem != NULL)
		{
			SetReserveState(*pCTreeChildItem);

			//遍历孩子兄弟
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

////循环遍历子节点
//while (!stackCTree.empty())
//{
//	CTreeItem *pCTreeChildItem = stackCTree.top();
//	stackCTree.pop();

//	//设置节点状态
//	pCTreeChildItem->SetItemState(1);

//	pCTreeChildItem = pCTreeChildItem->GetChildItem();
//	//把节点孩子压栈
//	if (pCTreeChildItem != NULL)
//	{
//		stackCTree.push(pCTreeChildItem->GetChildItem());
//	}

//	//把节点兄弟节点压栈
//	CTreeItem *pCTreeNextItem = pCTreeChildItem->GetNextItem();
//	while (pCTreeNextItem != NULL)
//	{
//		stackCTree.push(pCTreeNextItem);
//		pCTreeNextItem = pCTreeNextItem->GetNextItem();
//	}
//}

