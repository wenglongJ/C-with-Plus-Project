#pragma once
/*Watress.h*/
#include "MenuComponent.h"
class Watress
{
private:
	MenuComponent* allMenu;
public:
	Watress(MenuComponent* _allMenu) : allMenu(_allMenu) {}
	void printMenu()
	{
		allMenu->print();
	}

	~Watress() {};
};