#pragma once
/*MenuComponent.h*/
#include "UnsupportedOperationException.h"
#include <string>
class MenuComponent
{
public:
	MenuComponent() {}
	virtual ~MenuComponent() {}
	//此处做了抛出异常处理，下一篇文档完善这块代码
	virtual void add(MenuComponent* menuComponent)
	{
		throw new UnsupportedOperationException();
	}
	virtual void remove(MenuComponent* menuComponent)
	{
		throw new UnsupportedOperationException();
	}
	virtual MenuComponent* getChild(int i)
	{
		throw new UnsupportedOperationException();
	}
	virtual std::string getName()
	{
		throw new UnsupportedOperationException();
	}
	virtual std::string getDescription()
	{
		throw new UnsupportedOperationException();
	}
	virtual float getPrice()
	{
		throw new UnsupportedOperationException();
	}
	virtual bool isVegetarian()
	{
		throw new UnsupportedOperationException();
	}
	virtual void print()
	{
		throw new UnsupportedOperationException();
	}
};

/*Menu.h*/
#pragma once
#include "MenuComponent.h"
#include <vector>
#include <algorithm>
#include <iostream>
class Menu : public MenuComponent
{
private:
	std::vector<MenuComponent*> menuComponents;
	std::string name;
	std::string description;
public:
	Menu(std::string _name, std::string _description) :
		name(_name), description(_description) {}
	void add(MenuComponent* menuComponent)
	{
		menuComponents.push_back(menuComponent);
	}
	void remove(MenuComponent* menuComponent)
	{
		std::remove(menuComponents.begin(), menuComponents.end(), menuComponent);
	}
	MenuComponent* getChild(int i)
	{
		return menuComponents.at(i);
	}
	std::string getName()
	{
		return name;
	}
	std::string getDescription()
	{
		return description;
	}
	void print()
	{
		std::cout << "\n" + getName();
		std::cout << ", " + getDescription() << std::endl;
		std::cout << "---------------------" << std::endl;

		std::vector<MenuComponent*>::iterator it = menuComponents.begin();
		while (it != menuComponents.end())
		{
			MenuComponent* menuComponent = *it;
			it++;
			menuComponent->print();
		}
	}
	~Menu() {}
};

/*MenuItem.h*/
#pragma once
#include "MenuComponent.h"
#include <string>
#include <iostream>
class MenuItem : public MenuComponent
{
private:
	std::string name;
	std::string description;
	bool vegetarian;
	float price;
public:
	//MenuItem(std::string name,std::string description,bool vegetarian,float price)
	//{
	//	this->name = name;
	//	this->description = description;
	//	this->vegetarian = vegetarian;
	//	this->price = price;
	//}
	MenuItem(std::string _name, std::string _description, bool _vegetarian, float _price) :
		name(_name), description(_description), vegetarian(_vegetarian), price(_price) {}
	~MenuItem() {}
	std::string getName()
	{
		return name;
	}
	std::string getDescription()
	{
		return description;
	}
	float getPrice()
	{
		return price;
	}
	bool isVegetarian()
	{
		return vegetarian;
	}
	void print()
	{
		std::cout << "  " + getName();
		if (isVegetarian())
		{
			std::cout << "(V)";
		}
		std::cout << ", " << getPrice() << std::endl;
		std::cout << "    --" + getDescription() << std::endl;
	}
};