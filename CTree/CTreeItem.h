#pragma once

class CTreeItem
{
public:
	CTreeItem* GetChildItem();
	CTreeItem* GetNextItem();
	void SetItemState(int nState);
	int GetItemState();
};