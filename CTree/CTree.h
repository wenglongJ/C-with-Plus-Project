#pragma once

#include "CTreeItem.h"

class CTree
{
public:
	CTreeItem *GetRootItem();
	void SelectAll();
	void DeselectAll();
	void InvertSelection();

protected:
	void SetReserveState(CTreeItem &treeItem);
};